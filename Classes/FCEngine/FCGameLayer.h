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
    
    //get
    FCObject* getFCObject(int tag);
    
    //draw
    void drawTmpSprites(std::vector<cocos2d::Vec2> pos,const std::string& fname);
    void clearTmpSprites();
    
    void focusOn(cocos2d::Vec2 center,float scale,bool animate);
    void focusOn(cocos2d::Vec2 center,float scale,bool animate,cocos2d::CallFunc* complete);
    
    std::function<bool(int tx,int ty)> onClick;
    bool canTouchView = true;
    bool touchEnable = true;
private:
    cocos2d::Size _visibleSize;
    cocos2d::Size _mapSize;
    
    cocos2d::Vec2 _focusCenter;
    float _focusScale = 1.0f;
    bool _infiniteMap = true;
    
    //game
    cocos2d::TMXTiledMap* _map;
    cocos2d::Vector<cocos2d::Sprite*> _tmpSprite;
    
    int _touchMode;
};

#endif /* defined(__LHCocosFirstGame__FCGameLayer__) */
