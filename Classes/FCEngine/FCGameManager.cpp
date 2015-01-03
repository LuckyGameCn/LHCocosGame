//
//  FCGameManager.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-11-28.
//
//

#include "FCGameManager.h"
#include "FCGameConfig.h"

USING_NS_CC;

static FCGameManager* _instance =nullptr;

FCGameManager* FCGameManager::getInstance(){
    if (!_instance) {
        _instance = new  FCGameManager();
        _instance->init();
    }
    return _instance;
}

void FCGameManager::init(){
    for (int i = 0 ; i<actualTileMapHeight; i++) {
        for (int j = 0 ; j<actualTileMapWidth; j++) {
            map[i][j]= new Vector<FCObject*>();
        }
    }
}

void FCGameManager::clear(){
    for (int i = 0 ; i<actualTileMapHeight; i++) {
        for (int j = 0 ; j<actualTileMapWidth; j++) {
            map[i][j]->clear();
        }
    }
}

void FCGameManager::clickOn(std::function<bool(int tx,int ty)>& clicktile,float x, float y){
    int tx = x/fcTileSize;
    int ty = y/fcTileSize;
//    log("click %d,%d",tx,ty);
    auto vc = map[ty][tx];
    if (clicktile && clicktile(tx,ty)) {
        return;
    }else{
        for (auto it = vc->begin();it!=vc->end();it++) {
            if ((*it)->onClick) {
                bool res = (*it)->onClick(*it);
                if (res) {
                    break;
                }
            }
        }
    }
}

void FCGameManager::setTileMapSize(int width, int height){
    actualTileMapHeight = height;
    actualTileMapWidth = width;
}

void FCGameManager::changePosition(FCObject *fcobj, int tx, int ty){
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

bool FCGameManager::move(FCMoveObject *fcobj, int tx, int ty){
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

bool FCGameManager::isBlock(int tx, int ty){
    auto vc = getFCObjects(tx, ty);
    if(vc->size()==1&&vc->at(0)->mapType==FCMAPTYPE_BLOCK) return true;
    return false;
}

bool FCGameManager::isInMap(int tx, int ty){
    return (tx>=0&&tx<actualTileMapWidth&&ty>=0&&ty<actualTileMapHeight);
}

Vec2 FCGameManager::tileToPosition(int tx, int ty){
    float x = tx * fcTileSize + fcTileSize/2;
    float y = ty * fcTileSize + fcTileSize/2;
    return Vec2(x, y);
}

Vec2 FCGameManager::positionToTile(cocos2d::Vec2 &po){
    return Vec2(po.x/fcTileSize,po.y/fcTileSize);
}

cocos2d::Vector<FCObject*>* FCGameManager::getFCObjects(int tx, int ty){
    if (isInMap(tx, ty)) {
        auto vc = map[ty][tx];
        return vc;
    }else{
        return nullptr;
    }
}

FCObject* FCGameManager::getFCObject(const std::string &name){
    return nullptr;
}

FCObject* FCGameManager::getFCObject(int tx, int ty){
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

bool FCGameManager::removeFCObject(FCObject *fcobj){
    auto vc = map[fcobj->ty][fcobj->tx];
    if (vc->contains(fcobj)) {
        vc->eraseObject(fcobj);
        return true;
    }else{
        log("can not find FCObject in map.");
        return false;
    }
}

std::vector<Vec2> FCGameManager::getMoveAbleArea(FCUnit *unit){
    
    std::vector<std::vector<int>> graph;
    for (int i = 0 ; i<actualTileMapHeight; i++) {
        std::vector<int> line;
        for (int j=0; j<actualTileMapWidth; j++) {
            auto vc = map[i][j];
            if(vc->size()==1){
                line.push_back(vc->at(0)->mapType);
            }else{
                line.push_back(FCMAPTYPE_PASS);
            }
        }
        graph.push_back(line);
    }
    std::vector<Vec2> area = FCAlgo::B_Search(graph, Vec2(unit->tx, unit->ty), unit->moveValue);
    return area;
}

bool FCGameManager::addFCObject(Node* node,FCObject *fcobj){
    return this->addFCObject(node, fcobj, 0);
}

bool FCGameManager::addFCObject(cocos2d::Node *node, FCObject *fcobj, int zindex){
    CCASSERT(fcobj->tx>=0, "tx out of range");
    CCASSERT(fcobj->ty>=0, "ty out of range");
    CCASSERT(fcobj->tx<actualTileMapWidth, "tx out of range");
    CCASSERT(fcobj->ty<actualTileMapHeight, "ty out of range");
    auto vc = map[fcobj->ty][fcobj->tx];
    vc->pushBack(fcobj);
    fcobj->aSprite->setPosition(tileToPosition(fcobj->tx, fcobj->ty));
    node->addChild(fcobj->aSprite,zindex);
    return true;
}

bool FCGameManager::addFCObjects(Node* node,cocos2d::Vector<FCObject *> &fcobjs){
    for (auto obj : fcobjs) {
        bool res = addFCObject(node,obj);
        if (!res) {
            return false;
        }
    }
    return true;
}