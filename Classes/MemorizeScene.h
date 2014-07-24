//------.h
#ifndef __MEMORIZESCENE__
#define __MEMORIZESCENE__
#include "cocos2d.h"
#include "RemWord.h"
#include "UILayout.h"

class MemorizeScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(cocos2d::CCDictionary *dic);
	bool initDict(cocos2d::CCDictionary *dic);
	CREATE_FUNC(MemorizeScene);
    
    virtual ~MemorizeScene();
    void genWord();
private:
    cocos2d::Vector<RemWord*> words;
    cocos2d::ui::Layout *currentLay;
};
#endif