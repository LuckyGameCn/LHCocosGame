//------.cpp
#include "ShowAnswerScene.h"
USING_NS_CC;
Scene* ShowAnswerScene::createScene(cocos2d::CCDictionary *dic)
{
	auto scene = Scene::create();
	auto layer = ShowAnswerScene::create();
	layer->initDict(dic);
	scene->addChild(layer);
	return scene;
}

ShowAnswerScene::~ShowAnswerScene(){
}
bool ShowAnswerScene::initDict(cocos2d::CCDictionary *dic)
{
    cocos2d::CCString *answer;
    
    
	return true;
}
