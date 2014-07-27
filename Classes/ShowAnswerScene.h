//------.h
#ifndef __SHOWANSWERSCENE__
#define __SHOWANSWERSCENE__
#include "cocos2d.h"
class ShowAnswerScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(cocos2d::CCDictionary *dic);
	bool initDict(cocos2d::CCDictionary *dic);
	virtual ~ShowAnswerScene();
	CREATE_FUNC(ShowAnswerScene);
};
#endif
