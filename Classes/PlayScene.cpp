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
#include "FCGameController.h"
#include "FCGameManager.h"
#include "UIListView.h"
#include "FCGameController.h"

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
    _gameLayer->setMapSize(Size(1000,1000));
    _gameLayer->touchEnable=true;
    addChild(_gameLayer);
    
    FCGameController::getInstance()->onActionGet = [this](FCAction* fcac){
        if (fcac->acType==FCActionCreateUnit) {
            auto u1 = FCUnitFactory::createNomalSoldier((FCCreateUnitAction*)fcac);
            _gameLayer->addFCObject(u1);
            FCGameController::getInstance()->nextAction();
        }
    };
    FCGameController::getInstance()->connect();
    
    _gameLayer->onClick = [this](int tx,int ty){
        FCObject *obj = FCGameManager::getInstance()->getFCObject(tx, ty);
        if (strcmp(typeid(*obj).name(), "FCUnit")==0) {
            FCUnit *unit = (FCUnit*)obj;
            
            Size vs = Director::getInstance()->getVisibleSize();
            Vec2 vo = Director::getInstance()->getVisibleOrigin();
            auto rs = Director::getInstance()->getRunningScene();
            auto aclist = ui::ListView::create();
            Size ls = Size(vs.width/3*2,vs.height/3*2);
            aclist->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
            aclist->setBackGroundColor(Color3B::BLACK);
            aclist->setSize(ls);
            aclist->setPosition(Vec2(vo.x+vs.width/2-ls.width/2, vo.y+vs.height/2-ls.height/2));
            rs->addChild(aclist);
            
            std::vector<std::string> acs={"End","Move","Attack"};
            for (int i =0; i<acs.size(); i++) {
                auto txt = ui::Text::create(acs[i], "", 40);
                aclist->pushBackCustomItem(txt);
            }
            aclist->addEventListener([aclist,this](Ref*, ui::ListView::EventType tp){
                if (tp==ui::ListView::EventType::ON_SELECTED_ITEM_END) {
                    switch (aclist->getCurSelectedIndex()) {
                        case 0:
                            _gameLayer->touchEnable=false;
                            FCGameController::getInstance()->nextAction();
                            break;
                        case 1:
                            
                            break;
                        case 2:
                            
                            break;
                        default:
                            break;
                    }
                    aclist->removeFromParent();
                }
            });
        }
        return true;
    };
    
	return true;
}