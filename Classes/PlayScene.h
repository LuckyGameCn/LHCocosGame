//------.h
#ifndef __PLAYSCENE__
#define __PLAYSCENE__
#include "cocos2d.h"
#include "RemLan.h"
#include "UIText.h"
#include "UIButton.h"
#include "UILayout.h"
class PlayScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(cocos2d::CCDictionary *dic);
	bool initDict(cocos2d::CCDictionary *dic);
	CREATE_FUNC(PlayScene);
    
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    void update(float delta);
    
private:
    RemLan *remlan;
    void genWord();
    
    long _scorevalue;
    cocos2d::ui::Text *_score;
    
    float _timeuse;
    cocos2d::ui::Text *_time;
    
    int checkComplete(cocos2d::Ref *charbt);
    void scoreAndMoveOn();
    void wrongAn();
    void showAn(Ref*,cocos2d::ui::Widget::TouchEventType type);
    void enableAllCharBt(bool enable);
    
    std::u16string currentanswer;
    std::u16string currentedit;
    
    cocos2d::ui::Button *editbutton;
    cocos2d::ui::Layout *currentlayout;
};
#endif