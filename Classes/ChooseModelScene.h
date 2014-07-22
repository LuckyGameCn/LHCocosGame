//------.h
#ifndef __CHOOSEMODELSCENE__
#define __CHOOSEMODELSCENE__
#include "cocos2d.h"
class ChooseModelScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(cocos2d::CCDictionary *dic);
    bool initDict(cocos2d::CCDictionary *dic);
	CREATE_FUNC(ChooseModelScene);
};
#endif