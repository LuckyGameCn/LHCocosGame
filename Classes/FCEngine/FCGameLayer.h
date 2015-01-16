//
//  FCGameLayer.h
//  LHCocosFirstGame
//
//  Created by huji on 14-11-27.
//
//

#ifndef __LHCocosFirstGame__FCGameLayer__
#define __LHCocosFirstGame__FCGameLayer__

#include "cocos2d.h"
#include "FCObject.h"
#include "FCUnit.h"
#include "FCAlgo.h"

#define FOCUS_ANI_TIME 0.2f

class FCGameLayer : public cocos2d::Layer{
public:
    FCGameLayer();
    virtual ~FCGameLayer();
    
    bool init();
    CREATE_FUNC(FCGameLayer);
    
    void update(float delta);
    
    bool setTiledMap(const std::string& tiledmap,float ts,std::function<cocos2d::Vector<FCObject*>(cocos2d::TMXObjectGroup* group)> callback);
    bool setTileSize(float ts);
    float getTileSize();
    void setMapSize(cocos2d::Size ms);
    void setMapTileSize(int tw,int th);
    void setVisibleSize(cocos2d::Vec2 vs);
    
    bool addFCObject(FCObject* fcobj);
    bool addFCObject(FCObject* fcobj,int zindex);
    bool addFCObjects(cocos2d::Vector<FCObject*>& fcobjs);
    void clear();
    bool removeFCObject(FCObject* fcobj);
    
    //get
    cocos2d::Vector<FCObject*>* getFCObjects(int tx,int ty);
    FCObject* getFCObject(int tx,int ty);//return the first.
    FCObject* getFCObject(const std::string& name);
    FCObject* getFCObject(int tag);
    
    //draw
    void drawTmpSprites(std::vector<cocos2d::Vec2> pos,const std::string& fname);
    bool isInTmpSprites(int tx,int ty);
    void clearTmpSprites();
    std::vector<cocos2d::Vec2> getMoveAbleArea(FCUnit* unit);
    std::vector<cocos2d::Vec2> getActionAbleArea(FCUnit* unit,int range);
    
    void focusOn(cocos2d::Vec2 center,float scale,bool animate);
    void focusOn(cocos2d::Vec2 center,float scale,bool animate,cocos2d::CallFunc* complete);
    
    std::function<bool(int tx,int ty)> onClick;
    bool canTouchView = true;
    bool touchEnable = true;
    
    void clickOn(std::function<bool(int tx,int ty)>& clicktile,float x,float y);
    bool move(FCMoveObject* fcobj,int tx,int ty);
    void changePosition(FCObject* fcobj,int tx,int ty);
    
    cocos2d::Vec2 tileToPosition(int tx,int ty);
    cocos2d::Vec2 positionToTile(const cocos2d::Vec2& po);
    
    bool isBlock(int tx,int ty);
    bool isInMap(int tx,int ty);
private:
    float fcTileSize;
    cocos2d::Rect visible;
    
    cocos2d::Size _visibleSize;
    cocos2d::Size _mapSize;
    
    cocos2d::Vec2 _focusCenter;
    float _focusScale = 1.0f;
    bool _infiniteMap = true;
    
    //game
    cocos2d::TMXTiledMap* _map;
    cocos2d::Vector<cocos2d::Sprite*> _tmpSprite;
    
    int _touchMode;
    
    cocos2d::Vector<FCObject*>* map[MAXTILEMAP_HEIGHT][MAXTILEMAP_WIDTH];
    
    int actualTileMapWidth = MAXTILEMAP_WIDTH;
    int actualTileMapHeight = MAXTILEMAP_HEIGHT;
};

#endif /* defined(__LHCocosFirstGame__FCGameLayer__) */
