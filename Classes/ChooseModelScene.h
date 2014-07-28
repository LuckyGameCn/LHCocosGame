//------.h
#ifndef __CHOOSEMODELSCENE__
#define __CHOOSEMODELSCENE__
#include "cocos2d.h"
#include "RemLan.h"
class ChooseModelScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene(cocos2d::CCDictionary *dic);
    bool initDict(cocos2d::CCDictionary *dic);
	CREATE_FUNC(ChooseModelScene);
    
    virtual ~ChooseModelScene();
    
    CC_SYNTHESIZE_RETAIN(RemLan*, remlan, Remlan);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCString*, tolearn, Tolearn);
};
#endif