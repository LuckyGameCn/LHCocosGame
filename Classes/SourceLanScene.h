//
//  SourceLanScene.h
//  LHCocosFirstGame
//
//  Created by huji on 14-7-21.
//
//

#ifndef __LHCocosFirstGame__SourceLanScene__
#define __LHCocosFirstGame__SourceLanScene__

#include <iostream>
#include "cocos2d.h"

class SourceLanScene : public cocos2d::Layer{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(cocos2d::CCString* learn);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool initLearn(cocos2d::CCString* learn);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SourceLanScene);
    
    virtual ~SourceLanScene();
    CC_SYNTHESIZE_RETAIN(cocos2d::CCString*, tolearn, Tolearn);
    
private:
    cocos2d::Vector<cocos2d::CCString*> _sources;
};

#endif /* defined(__LHCocosFirstGame__SourceLanScene__) */
