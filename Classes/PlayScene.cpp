//------.cpp
#include "PlayScene.h"
#include "ThirdPartyHelper.h"
#include "UIButton.h"
#include "UIText.h"
#include "LHMacros.h"
USING_NS_CC;
Scene* PlayScene::createScene(cocos2d::CCDictionary *dic)
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
    layer->initWithColor(Color4B::BLACK);
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
    Size vs = Director::getInstance()->getVisibleSize();
    Vec2 vo = Director::getInstance()->getVisibleOrigin();
    
    auto text = ui::Text::create("Text哈哈.>?[]{}", Common_Font, 60);
    text->setPosition(Vec2(vs.width/2, vs.height/2));
    text->setColor(Color3B::WHITE);
    addChild(text);
    
	return true;
}