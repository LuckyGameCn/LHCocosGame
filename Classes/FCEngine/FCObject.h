//
//  FCObject.h
//  LHCocosFirstGame
//
//  Created by huji on 14-11-28.
//
//

#ifndef __LHCocosFirstGame__FCObject__
#define __LHCocosFirstGame__FCObject__

#include "cocos2d.h"

class FCGameLayer;

#define FCMAPTYPE_BLOCK -1
#define FCMAPTYPE_PASS 0

const static cocos2d::Vec2 FCOBJ_DI_UP(0,1);
const static cocos2d::Vec2 FCOBJ_DI_DOWN(0,-1);
const static cocos2d::Vec2 FCOBJ_DI_LEFT(-1,0);
const static cocos2d::Vec2 FCOBJ_DI_RIGHT(1,0);

class FCObject : public cocos2d::Ref{
public:
    typedef enum{
        UP = 0,RIGHT = 1,DOWN = 2,LEFT = 3
    }DIRECTION;
    
    bool init(const std::string& filename,FCGameLayer *gamelayer);
    bool init(const std::string& filename,const std::string& name,FCGameLayer *gamelayer);
    
    virtual ~FCObject(){
        aSprite->removeFromParent();
        aSprite->release();
    };
    
    //member
    int tx;
    int ty;
    int tag;
    cocos2d::Sprite* aSprite;
    int mapType = FCMAPTYPE_BLOCK;
    bool clickEnable = false;
    
    //true means handled.do not pass on.
    std::function<bool(FCObject* me)> onClick;
    std::function<bool(FCObject* fcobj)> onObjectDidEnter;
    
    //func
    FCGameLayer* getGameLayer();
    const std::string& getName();
    void setDirection(cocos2d::Vec2 direction);
    virtual void changePosition(int tx,int ty);
    cocos2d::Vec2 getDirection();
    void removeSelf();
protected:
    FCGameLayer *_gameLayer;
private:
    std::string _name;
    cocos2d::Vec2 _direction = FCOBJ_DI_UP;
};

#endif /* defined(__LHCocosFirstGame__FCObject__) */
