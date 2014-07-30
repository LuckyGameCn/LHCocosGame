//------.h
#ifndef __PLAYSCENE__
#define __PLAYSCENE__
#include "cocos2d.h"
USING_NS_CC;
class PlayScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene(cocos2d::CCDictionary *dic);
	bool initDict(cocos2d::CCDictionary *dic);
	virtual ~PlayScene();
	CREATE_FUNC(PlayScene);
};
#endif