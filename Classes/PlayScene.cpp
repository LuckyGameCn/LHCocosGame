//------.cpp
#include "PlayScene.h"
#include "ThirdPartyHelper.h"
USING_NS_CC;
Scene* PlayScene::createScene(cocos2d::CCDictionary *dic)
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
    layer->initWithColor(Color4B::WHITE);
	layer->initDict(dic);
	scene->addChild(layer);
	return scene;
}

PlayScene::~PlayScene(){
}

void PlayScene::update(float delta){
    
}

bool PlayScene::initDict(cocos2d::CCDictionary *dic)
{
    DelayTime *time = DelayTime::create(15);
    CallFunc *call = CallFunc::create([](){
    ThirdPartyHelper::setAd(SET_AD_SCREEN);
    });
    auto sq = Sequence::create(time,call, NULL);
    this->runAction(sq);
	return true;
}