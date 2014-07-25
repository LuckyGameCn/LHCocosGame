//------.h
#ifndef __PLAYSCENE__
#define __PLAYSCENE__
#include "cocos2d.h"
#include "RemLan.h"
#include "UIText.h"
class PlayScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(cocos2d::CCDictionary *dic);
	bool initDict(cocos2d::CCDictionary *dic);
	CREATE_FUNC(PlayScene);
    
    virtual void OnEnt
    
private:
    RemLan *remlan;
    void genWord();
    
    float _scorevalue;
    cocos2d::ui::Text *_score;
};
#endif