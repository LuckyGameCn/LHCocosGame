//------.cpp
#include "PlayScene.h"
Scene* PlayScene::createScene(cocos2d::CCDictionary *dic)
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
	layer->initDict(dic);
	scene->addChild(layer);
	return scene;
}

PlayScene::~PlayScene(){
}
bool PlayScene::initDict(cocos2d::CCDictionary *dic)
{
    
	return true;
}