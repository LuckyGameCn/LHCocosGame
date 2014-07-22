//------.cpp
#include "MemorizeScene.h"
#include "RemLan.h"
#include "UIText.h"
#include "UIButton.h"
USING_NS_CC;
Scene* MemorizeScene::createScene(cocos2d::CCDictionary *dic)
{
	auto scene = Scene::create();
    scene->setTag(624);
	auto layer = MemorizeScene::create();
	layer->initDict(dic);
	scene->addChild(layer);
	return scene;
}

bool MemorizeScene::initDict(cocos2d::CCDictionary *dic)
{
    RemLan *lan = (RemLan*)dic->objectForKey("lan");
    words = lan->words;
    
    this->genWord();
    
    cocos2d::ui::Button *bt = cocos2d::ui::Button::create("play.png");
    bt->addTouchEventListener([](Ref*,cocos2d::ui::Widget::TouchEventType){
        Director::getInstance()->popScene();
    });
    bt->setPosition(Vec2(40, 40));
    this->addChild(bt,1);
    
	return true;
}

MemorizeScene::~MemorizeScene(){
    
}

void MemorizeScene::genWord(){
    Size vs = Director::getInstance()->getVisibleSize();
    
    auto lay = cocos2d::ui::Layout::create();
    lay->setPosition(Vec2(vs.width,0));
    lay->setSize(vs);
//    lay->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//    lay->setBackGroundColor(Color3B::BLUE);
    lay->setTouchEnabled(true);
    lay->addTouchEventListener([this,vs](Ref* ps,cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            auto c = this->currentLay;
            auto mva = cocos2d::MoveTo::create(0.3, Vec2(0, -vs.height));
            auto rma = cocos2d::CallFuncN::create([](Node *nd){
                nd->removeFromParent();
            });
            auto sq = cocos2d::Sequence::create(mva,rma, NULL);
            c->runAction(sq);
            this->genWord();
        }
    });
    this->addChild(lay, 0);
    
    int index = CCRANDOM_0_1() * words.size();
    RemWord *w = words.at(index);
    auto lwt = cocos2d::ui::Text::create(w->getLearn()->getCString(), "Arial", 60);
    lwt->setColor(Color3B::BLACK);
    lwt->setPosition(Vec2(vs.width/2, vs.height/2));
    lay->addChild(lwt);
    auto swt = cocos2d::ui::Text::create(w->getSource()->getCString(),"Arial", 40);
    swt->setPosition(Vec2(vs.width/2, vs.height/2-200));
    lay->addChild(swt);
    
    auto mva = cocos2d::MoveTo::create(0.5, Vec2(0, 0));
    lay->runAction(mva);
    
    currentLay = lay;
}