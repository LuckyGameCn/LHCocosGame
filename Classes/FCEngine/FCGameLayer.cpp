//
//  FCGameLayer.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-11-27.
//
//

#include "FCGameLayer.h"
#include "FCGameManager.h"
#include "FCGameConfig.h"

#define FCTOUCHMODE_INIT 0
#define FCTOUCHMODE_VIEW 1

USING_NS_CC;
FCGameLayer::FCGameLayer(){
}

FCGameLayer::~FCGameLayer(){
    this->getEventDispatcher()->removeEventListenersForTarget(this);
    FCGameManager::getInstance()->clear();
}

bool FCGameLayer::init(){
    _mapSize = Size(0,0);
    focusOn(Vec2(0, 0), -1, false);
    
    auto lis = EventListenerTouchOneByOne::create();
    lis->onTouchBegan = [this](Touch* tmpTouch, Event*){
        if(!touchEnable) return false;
        _touchMode = FCTOUCHMODE_INIT;
        return true;
    };
    lis->onTouchMoved = [this](Touch* tmpTouch, Event*){
        if (canTouchView) {
            _touchMode = FCTOUCHMODE_VIEW;
            Vec2 current = tmpTouch->getLocation();
            Vec2 pre = tmpTouch->getPreviousLocation();
            pre.subtract(current);
            pre.add(_focusCenter);
            this->focusOn(pre, _focusScale, false);
        }
    };
    lis->onTouchEnded = [this](Touch* tmptouch, Event*){
        if (_touchMode==FCTOUCHMODE_INIT) {
            Size vs = _visibleSize;
            Vec2 tp = tmptouch->getLocation();
            tp.subtract(Vec2(vs.width/2, vs.height/2));
            tp.scale(1/this->getScale());
            tp.add(_focusCenter);
            FCGameManager::getInstance()->clickOn(onClick, tp.x, tp.y);
        }
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, this);
    
    return true;
}

void FCGameLayer::update(float delta){
    
}

void FCGameLayer::setMapSize(cocos2d::Size ms){
    _infiniteMap = false;
    _mapSize = ms;
}

void FCGameLayer::setVisibleSize(cocos2d::Vec2 vs){
    _visibleSize = vs;
}

FCObject* FCGameLayer::getFCObject(int tag){
    return FCGameManager::getInstance()->getFCObject(tag);
}

void FCGameLayer::drawTmpSprites(std::vector<cocos2d::Vec2> pos,const std::string& fname){
    clearTmpSprites();
    for (auto v : pos){
        auto sp = Sprite::create(fname);
        sp->setPosition(FCGameManager::getInstance()->tileToPosition(v.x, v.y));
        addChild(sp);
        _tmpSprite.pushBack(sp);
    }
}

void FCGameLayer::clearTmpSprites(){
    if (_tmpSprite.size()==0) {
        return;
    }
    for (auto sp : _tmpSprite){
        sp->removeFromParent();
    }
    _tmpSprite.clear();
}

bool FCGameLayer::setTiledMap(const std::string &tiledmap,float ts,std::function<cocos2d::Vector<FCObject*>(TMXObjectGroup* group)> callback){
    _map = TMXTiledMap::create(tiledmap);
    if (!_map) {
        return false;
    }
    
    FCGameManager::getInstance()->fcTileSize = ts;
    
    setMapSize(Size(_map->getTileSize().width*_map->getMapSize().width, _map->getTileSize().height*_map->getMapSize().height));
    _map->setPosition(0, 0);
    addChild(_map);
    
    int tmptw = ts;
    int tmpth = ts;
    int tmpmw = _mapSize.width;
    int tmpmh = _mapSize.height;
    CCASSERT(tmpmw%tmptw==0, "tile width and map width not ok");
    CCASSERT(tmpmh%tmpth==0, "tile height and map height not ok");
    
    focusOn(Vec2(_mapSize.width/2, _mapSize.height/2), -1,false);
    
    const auto ogs = _map->getObjectGroups();
    for ( auto og : ogs) {
        Vector<FCObject*> objs = callback(og);
        addFCObjects(objs);
    }
    return true;
}

bool FCGameLayer::setTileSize(float ts){
    FCGameManager::getInstance()->fcTileSize = ts;
    return true;
}

float FCGameLayer::getTileSize(){
    return FCGameManager::getInstance()->fcTileSize;
}

bool FCGameLayer::addFCObject(FCObject *fcobj){
    return FCGameManager::getInstance()->addFCObject(this,fcobj);
}

bool FCGameLayer::addFCObject(FCObject *fcobj, int zindex){
    return FCGameManager::getInstance()->addFCObject(this, fcobj, zindex);
}

bool FCGameLayer::addFCObjects(cocos2d::Vector<FCObject *> &fcobjs){
    return FCGameManager::getInstance()->addFCObjects(this, fcobjs);
}

void FCGameLayer::clear(){
    cleanup();
    removeAllChildren();
    FCGameManager::getInstance()->clear();
}

void FCGameLayer::focusOn(cocos2d::Vec2 center, float toscale, bool animate, cocos2d::CallFunc *complete){
    
    Size vs = _visibleSize;
    Vec2 vo(0,0);
    
    if (toscale<=0) toscale = _focusScale;
    
    Vec2 sccenter = Vec2(vs.width/2+vo.x, vs.height/2 + vo.y);
    
    float tox = sccenter.x - center.x*toscale;
    float toy = sccenter.y - center.y*toscale;
    
    if (!_infiniteMap) {
        if (toy>vo.y) {
            toy = vo.y;
        }else if (toy<vs.height-toscale*_mapSize.height+vo.y){
            toy = vs.height-toscale*_mapSize.height+vo.y;
        }
        
        if (tox>vo.x) {
            tox = vo.x;
        }else if (tox<vs.width-toscale*_mapSize.width+vo.x){
            tox = vs.width-toscale*_mapSize.width+vo.x;
        }
    }
    
    if (animate) {
        auto scale = ScaleTo::create(FOCUS_ANI_TIME, toscale);
        auto mv = MoveTo::create(FOCUS_ANI_TIME, Vec2(tox, toy));
        auto conc = Spawn::create(scale,mv, NULL);
        if (complete==nullptr) {
            this->runAction(conc);
        }else{
            auto sq = Sequence::create(conc,complete, NULL);
            this->runAction(sq);
        }
    }else{
        this->setPosition(tox, toy);
        this->setScale(toscale);
    }
    
    _focusCenter = Vec2((sccenter.x - tox)/toscale, (sccenter.y - toy)/toscale);
    _focusScale = toscale;
    
    //setvisible bounding.
    int x = (_focusCenter.x - vs.width/2/toscale);
    int y = (_focusCenter.y - vs.height/2/toscale);
    int w = vs.width/toscale;
    int h = vs.height/toscale;
    FCGameManager::getInstance()->visible = Rect(x, y, w, h);
}

void FCGameLayer::focusOn(cocos2d::Vec2 center, float len, bool animate){
    this->focusOn(center, len, animate, nullptr);
}