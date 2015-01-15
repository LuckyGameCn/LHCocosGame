//
//  FCGameManager.h
//  LHCocosFirstGame
//
//  Created by huji on 14-11-28.
//
//

#ifndef __LHCocosFirstGame__FCGameManager__
#define __LHCocosFirstGame__FCGameManager__

#include "cocos2d.h"
#include "FCObject.h"
#include "FCMoveObject.h"
#include "FCUnit.h"
#include "FCAlgo.h"

class FCGameManager{
public:
    static FCGameManager* getInstance();

    float fcTileSize;
    cocos2d::Rect visible;
    
    void setTileMapSize(int width,int height);
    
    bool addFCObject(cocos2d::Node* node,FCObject* fcobj);
    bool addFCObject(cocos2d::Node* node,FCObject* fcobj,int zindex);
    bool addFCObjects(cocos2d::Node* node,cocos2d::Vector<FCObject*>& fcobjs);
    cocos2d::Vector<FCObject*>* getFCObjects(int tx,int ty);
    FCObject* getFCObject(int tx,int ty);//return the first.
    FCObject* getFCObject(const std::string& name);
    FCObject* getFCObject(int tag);
    bool removeFCObject(FCObject* fcobj);
    
    std::vector<cocos2d::Vec2> getMoveAbleArea(FCUnit* unit);
    std::vector<cocos2d::Vec2> getActionAbleArea(FCUnit* unit,int range);
    
    void clickOn(std::function<bool(int tx,int ty)>& clicktile,float x,float y);
    bool move(FCMoveObject* fcobj,int tx,int ty);
    void changePosition(FCObject* fcobj,int tx,int ty);
    
    cocos2d::Vec2 tileToPosition(int tx,int ty);
    cocos2d::Vec2 positionToTile(cocos2d::Vec2& po);
    
    bool isBlock(int tx,int ty);
    bool isInMap(int tx,int ty);
    
    void clear();
private:
    void init();
    
    cocos2d::Vector<FCObject*>* map[MAXTILEMAP_HEIGHT][MAXTILEMAP_WIDTH];
    
    int actualTileMapWidth = MAXTILEMAP_WIDTH;
    int actualTileMapHeight = MAXTILEMAP_HEIGHT;
};

#endif /* defined(__LHCocosFirstGame__FCGameManager__) */
