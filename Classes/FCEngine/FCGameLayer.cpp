//
//  FCGameLayer.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-11-27.
//
//

#include "FCGameLayer.h"
#include "FCGameConfig.h"

#define FCTOUCHMODE_INIT 0
#define FCTOUCHMODE_VIEW 1

USING_NS_CC;
FCGameLayer::FCGameLayer(){
}

FCGameLayer::~FCGameLayer(){
    this->getEventDispatcher()->removeEventListenersForTarget(this);
    
    clear();
}

bool FCGameLayer::init(){
    _mapSize = Size(0,0);
    focusOn(Vec2(0, 0), -1, false);
    
    for (int i = 0 ; i<actualTileMapHeight; i++) {
        for (int j = 0 ; j<actualTileMapWidth; j++) {
            map[i][j]= new Vector<FCObject*>();
        }
    }
    
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
            clickOn(onClick, tp.x, tp.y);
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

bool FCGameLayer::setTiledMap(const std::string &tiledmap,float ts,std::function<cocos2d::Vector<FCObject*>(TMXObjectGroup* group)> callback){
    _map = TMXTiledMap::create(tiledmap);
    if (!_map) {
        return false;
    }
    
    fcTileSize = ts;
    
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
    fcTileSize = ts;
    return true;
}

float FCGameLayer::getTileSize(){
    return fcTileSize;
}

void FCGameLayer::enumerateMap(const std::function<bool (int, int, cocos2d::Vector<FCObject *> *)> &callback){
    
}

void FCGameLayer::drawRange(FCSkill *skill, const std::string &name){
    std::vector<cocos2d::Vec2> *range = skill->onSkillRange();
    for (auto vc =range->begin() ;vc!=range->end();vc++) {
        Vec2 po = *vc;
        auto sp = Sprite::create(name);
        sp->setPosition(tileToPosition(po.x, po.y));
        sp->setTag(-1);//tag < 0.tmp sprite.
        addChild(sp);
    }
    _rangeSkill = skill;
}

void FCGameLayer::clearRange(){
    Vector<Node*> cdren = getChildren();
    for (auto nd = cdren.begin(); nd!=cdren.end(); nd++) {
        if ((*nd)->getTag()<0) {
            (*nd)->removeFromParent();
        }
    }
    _rangeSkill = nullptr;
}

bool FCGameLayer::addFCObject(FCObject *fcobj){
    return this->addFCObject(fcobj, 0);
}

bool FCGameLayer::addFCObject(FCObject *fcobj, int zindex){
    CCASSERT(fcobj->tx>=0, "tx out of range");
    CCASSERT(fcobj->ty>=0, "ty out of range");
    CCASSERT(fcobj->tx<actualTileMapWidth, "tx out of range");
    CCASSERT(fcobj->ty<actualTileMapHeight, "ty out of range");
    auto vc = map[fcobj->ty][fcobj->tx];
    vc->pushBack(fcobj);
    fcobj->aSprite->setPosition(tileToPosition(fcobj->tx, fcobj->ty));
    this->addChild(fcobj->aSprite,zindex);
    return true;
}

bool FCGameLayer::addFCObjects(cocos2d::Vector<FCObject *> &fcobjs){
    for (auto obj : fcobjs) {
        bool res = addFCObject(obj);
        if (!res) {
            return false;
        }
    }
    return true;
}


cocos2d::Vector<FCObject*>* FCGameLayer::getFCObjects(int tx, int ty){
    if (isInMap(tx, ty)) {
        auto vc = map[ty][tx];
        return vc;
    }else{
        return nullptr;
    }
}

FCObject* FCGameLayer::getFCObject(const std::string &name){
    return nullptr;
}

FCObject* FCGameLayer::getFCObject(int tag){
    for (int i = 0 ; i<actualTileMapHeight; i++) {
        for (int j=0; j<actualTileMapWidth; j++) {
            auto vc = map[i][j];
            for ( auto obj : *vc ){
                if (obj->tag==tag) {
                    return obj;
                }
            }
        }
    }
    return nullptr;
}

FCObject* FCGameLayer::getFCObject(int tx, int ty){
    auto vc = getFCObjects(tx, ty);
    if (vc) {
        if (vc->size()>0) {
            return vc->at(vc->size()-1);
        }else{
            return nullptr;
        }
    }else{
        return nullptr;
    }
}

bool FCGameLayer::removeFCObject(FCObject *fcobj){
    auto vc = map[fcobj->ty][fcobj->tx];
    if (vc->contains(fcobj)) {
        vc->eraseObject(fcobj);
        return true;
    }else{
        log("can not find FCObject in map.");
        return false;
    }
}

void FCGameLayer::clickOn(std::function<bool(int tx,int ty)>& clicktile,float x, float y){
    int tx = x/fcTileSize;
    int ty = y/fcTileSize;
    auto vc = map[ty][tx];
    
    if (_rangeSkill&&_rangeSkill->onDrawedRangeClick) {
        if(_rangeSkill->onDrawedRangeClick(tx,ty,vc)){
            this->clearRange();
        }
        return;
    }
    
    if (clicktile && clicktile(tx,ty)) {
        return;
    }else{
        for (auto it = vc->begin();it!=vc->end();it++) {
            if((*it)->clickEnable){
                if ((*it)->onClick) {
                    bool res = (*it)->onClick(*it);
                    if (res) {
                        break;
                    }
                }
            }else{
                break;
            }
        }
    }
}

bool FCGameLayer::move(FCMoveObject *fcobj, int tx, int ty){
    if (tx == fcobj->tx && ty == fcobj->ty) {
        return false;
    }
    if (tx<0||tx>=actualTileMapWidth){
        return false;
    }
    if (ty<0||ty>=actualTileMapHeight){
        return false;
    }
    
    int startx;
    int starty;
    int endx;
    int endy;
    
    int searchx;
    int searchy;
    int searchW;
    int searchH;
    if (fcobj->pathFindVisible) {
        searchx = visible.origin.x/fcTileSize;
        searchy = visible.origin.y/fcTileSize;
        searchW = ceilf(visible.getMaxX()/fcTileSize)-searchx;
        searchH = ceilf(visible.getMaxY()/fcTileSize)-searchy;
        startx = fcobj->tx-searchx;
        starty = fcobj->ty-searchy;
        endx = tx-searchx;
        endy = ty-searchy;
        CCASSERT((startx>=0&&startx<searchW&&starty>=0&&starty<searchH), "start not visible.");
        CCASSERT((endx>=0&&endx<searchW&&endy>=0&&endy<searchH), "end not visible.");
    }else{
        searchx = 0;
        searchy = 0;
        searchW = actualTileMapWidth;
        searchH = actualTileMapHeight;
        startx = fcobj->tx;
        starty = fcobj->ty;
        endx = tx;
        endy = ty;
    }
    //    printf("%d,%d w%d,h%d sx%d,sy%d\n",endx,endy,searchW,searchH,searchx,searchy);
    std::vector<std::vector<int>> graph;
    for (int i = searchy ; i<searchy+searchH; i++) {
        std::vector<int> line;
        for (int j=searchx; j<searchx+searchW; j++) {
            auto vc = map[i][j];
            if(vc->size()==1){
                line.push_back(vc->at(0)->mapType);
            }else{
                line.push_back(FCMAPTYPE_PASS);
            }
        }
        graph.push_back(line);
    }
    std::vector<Vec2> *path = FCAlgo::A_Star(graph, Vec2(startx, starty), Vec2(endx, endy));
    if (path->size()==0) {
        return false;
    }
    if (fcobj->pathFindVisible) {
        for (auto &pv : *path) {
            pv.add(Vec2(searchx, searchy));
        }
    }
    
    if (fcobj->onMoveBegin) fcobj->onMoveBegin();
    Vec2 last = fcobj->aSprite->getPosition();
    Vector<FiniteTimeAction*> mvs;
    for (auto po : *path) {
        mvs.pushBack(CallFunc::create([this,fcobj,po](){
            if (fcobj->onMoveWillMove) fcobj->onMoveWillMove(fcobj,po.x,po.y);
            if (this->isBlock(po.x, po.y)){
                fcobj->aSprite->stopActionByTag(FCMOVEACTIONTAG);
                if (fcobj->onMoveEnd) fcobj->onMoveEnd();
            }
        }));
        Vec2 topo = tileToPosition(po.x, po.y);
        mvs.pushBack(MoveTo::create(topo.distance(last)/fcobj->moveSpeed, topo));
        last = topo;
        CallFunc *mvcall = CallFunc::create([this,fcobj,po](){
            int fromx = fcobj->tx;
            int fromy = fcobj->ty;
            this->changePosition(fcobj, po.x, po.y);
            if (fcobj->onMoveDidMove) fcobj->onMoveDidMove(fcobj,fromx,fromy);
        });
        mvs.pushBack(mvcall);
    }
    mvs.pushBack(CallFunc::create([fcobj](){
        if (fcobj->onMoveEnd) fcobj->onMoveEnd();
    }));
    auto sq = Sequence::create(mvs);
    sq->setTag(FCMOVEACTIONTAG);
    fcobj->aSprite->runAction(sq);
    delete path;
    return true;
}

void FCGameLayer::changePosition(FCObject *fcobj, int tx, int ty){
    if (tx==fcobj->tx && ty==fcobj->ty) {
        return;
    }
    fcobj->retain();
    map[fcobj->ty][fcobj->tx]->eraseObject(fcobj);
    
    auto vc = map[ty][tx];
    for(auto tmp : *vc){
        if (tmp->onObjectDidEnter) {
            if (tmp->onObjectDidEnter(fcobj)) {
                break;
            }
        }
    }
    
    fcobj->tx = tx;
    fcobj->ty = ty;
    map[ty][tx]->pushBack(fcobj);
    fcobj->release();
    
    fcobj->aSprite->setPosition(tileToPosition(tx, ty));
}

bool FCGameLayer::isBlock(int tx, int ty){
    auto vc = getFCObjects(tx, ty);
    if(vc->size()==1&&vc->at(0)->mapType==FCMAPTYPE_BLOCK) return true;
    return false;
}

bool FCGameLayer::isInMap(int tx, int ty){
    return (tx>=0&&tx<actualTileMapWidth&&ty>=0&&ty<actualTileMapHeight);
}

Vec2 FCGameLayer::tileToPosition(int tx, int ty){
    float x = tx * fcTileSize + fcTileSize/2;
    float y = ty * fcTileSize + fcTileSize/2;
    return Vec2(x, y);
}

Vec2 FCGameLayer::positionToTile(const cocos2d::Vec2 &po){
    return Vec2(po.x/fcTileSize,po.y/fcTileSize);
}

void FCGameLayer::clear(){
    cleanup();
    removeAllChildren();
    
    //clear
    for (int i = 0 ; i<actualTileMapHeight; i++) {
        for (int j = 0 ; j<actualTileMapWidth; j++) {
            map[i][j]->clear();
        }
    }
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
    visible = Rect(x, y, w, h);
}

void FCGameLayer::focusOn(cocos2d::Vec2 center, float len, bool animate){
    this->focusOn(center, len, animate, nullptr);
}