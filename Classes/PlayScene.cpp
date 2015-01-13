//------.cpp
#include "PlayScene.h"
#include "ThirdPartyHelper.h"
#include "UIButton.h"
#include "UIText.h"
#include "LHMacros.h"
#include "LocalizedString.h"
#include "LHGameChat.h"
#include "UITextField.h"
#include "FCUnitFactory.h"
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
    Size vs = Director::getInstance()->getVisibleSize();
    Vec2 vo = Director::getInstance()->getVisibleOrigin();
    
    _gameLayer = FCGameLayer::create();
    _gameLayer->setPosition(vo.x, vo.y);
    _gameLayer->setTileSize(128);
    addChild(_gameLayer);
    
    std::function<bool(FCObject *me)> onClick = [this](FCObject *me){
        
        return true;
    };
    
    auto u1 = FCUnitFactory::createNomalSoldier();
    u1->tx = 3;
    u1->ty = 4;
    u1->team = 1;
    u1->onClick = onClick;
    auto u2 = FCUnitFactory::createNomalSoldier();
    u2->tx = 5;
    u2->ty = 5;
    u2->team = 2;
    _gameLayer->addFCObject(u1);
    _gameLayer->addFCObject(u2);
    _gameLayer->onClick = [this,u1](int tx,int ty){
        u1->move(tx, ty);
        return false;
    };
    
    //game chat
    auto bt = LHGameChat::gameChatButton();
    bt->setPosition(Vec2(300, 300));
    this->addChild(bt);
    
	return true;
}