//------.cpp
#include "PlayScene.h"
#include "ThirdPartyHelper.h"
#include "UIButton.h"
#include "UIText.h"
#include "LHMacros.h"
#include "LocalizedString.h"
#include "LHGameChat.h"
#include "UITextField.h"
#include "FCGameController.h"
#include "UIListView.h"
#include "FCGameController.h"

//factory
#include "FCUnitFactory.h"

//actions
#include "FCControlAction.h"
#include "FCMoveAction.h"
#include "FCShowUIAction.h"
#include "FCAttackAction.h"

#define FCGL_STA_VIEW 0
#define FCGL_STA_MOVE 1
#define FCGL_STA_ATTACK 2

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

static void test(){
    FCCreateUnitAction *ac = new FCCreateUnitAction();
    ac->autorelease();
    ac->tag=1;
    ac->tx=3;
    ac->ty=4;
    FCGameController::getInstance()->onActionGet(ac);
    
    ac = new FCCreateUnitAction();
    ac->autorelease();
    ac->tag=2;
    ac->tx=4;
    ac->ty=4;
    FCGameController::getInstance()->onActionGet(ac);
    
    FCControlAction *cac = new FCControlAction();
    cac->ttag=1;
    FCGameController::getInstance()->onActionGet(cac);
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
    _gameLayer->setTag(FCGL_STA_VIEW);
    addChild(_gameLayer);
    
    _gameLayer->onClick = [this](int tx,int ty){
        
        return false;
    };
    
    std::function<bool(FCObject* me)> unitOnClick =  [this](FCObject* me){
        FCUnit *unit = (FCUnit*)me;
        
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
        
        auto skills = unit->getSkills();
        for (int i =0; i<skills.size(); i++) {
            auto skill = skills.at(i);
            auto txt = ui::Text::create(skill->name, "", 40);
            aclist->pushBackCustomItem(txt);
        }
        aclist->addEventListener([aclist,this,skills](Ref*, ui::ListView::EventType tp){
            if (tp==ui::ListView::EventType::ON_SELECTED_ITEM_END) {
                auto skill = skills.at(aclist->getCurSelectedIndex());
                skill->onSkillClick();
                aclist->removeFromParent();
            }
        });
        return true;
    };
    
    FCGameController::getInstance()->onActionGet = [this,unitOnClick,vo,vs](FCAction* fcac){
        if (fcac->acType==FCActionCreateUnit) {
            auto u1 = FCUnitFactory::createNomalSoldier((FCCreateUnitAction*)fcac,_gameLayer);
            u1->onClick = unitOnClick;
            _gameLayer->addFCObject(u1);
            FCGameController::getInstance()->nextAction();
        }else if(fcac->acType==FCActionControl){
            FCControlAction *ca = (FCControlAction *)fcac;
            _gameLayer->getFCObject(ca->ttag)->clickEnable=true;
        }else if(fcac->acType==FCActionMove){
            FCMoveAction *mv = (FCMoveAction*)fcac;
            FCMoveObject *mvo = (FCMoveObject*)_gameLayer->getFCObject(mv->ttag);
            mvo->onMoveEnd = [](){
                FCGameController::getInstance()->nextAction();
            };
            mvo->move(mv->tx, mv->ty);
        }else if(fcac->acType==FCActionAttack){
            FCAttackAction *at = (FCAttackAction*)fcac;
            FCUnit *from = (FCUnit*) _gameLayer->getFCObject(at->ftag);
            FCUnit *to = (FCUnit*) _gameLayer->getFCObject(at->ttag);
            from->attack(to, [](){
                FCGameController::getInstance()->nextAction();
            });
        }else if(fcac->acType==FCActionShowUI){
            FCShowUIAction *su = (FCShowUIAction*)fcac;
            auto text = ui::Text::create(su->content, "", 40);
            text->setColor(Color3B::GREEN);
            text->setPosition(Vec2(vo.x+vs.width/2, vo.y+vs.height/2));
            this->addChild(text);
            auto dl = DelayTime::create(1);
            auto sc = ScaleTo::create(0.3, 0.3);
            auto rs = RemoveSelf::create();
            auto call = CallFunc::create([]{
                FCGameController::getInstance()->nextAction();
            });
            auto sq = Sequence::create(dl,sc,rs,call, NULL);
            text->runAction(sq);
        }
    };
    FCGameController::getInstance()->connect();
    
    test();
    
	return true;
}