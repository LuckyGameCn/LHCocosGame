//
//  SourceLanScene.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-7-21.
//
//

#include "SourceLanScene.h"
#include "UIListView.h"
#include "UIText.h"
#include "UIButton.h"
#include "HelloWorldScene.h"
#include "ChooseModelScene.h"
#include "DeveloperInfoScence.h"

USING_NS_CC;

Scene* SourceLanScene::createScene(cocos2d::CCString* learn)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SourceLanScene::create();
    layer->initWithColor(Color4B::WHITE);
    layer->initLearn(learn);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

SourceLanScene::~SourceLanScene(){
    CC_SAFE_RELEASE(tolearn);
}

bool SourceLanScene::initLearn(cocos2d::CCString* learn){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (learn->compare("German")==0) {
        _sources.pushBack(cocos2d::CCString::create("中文"));
    }else if(learn->compare("English")){
        _sources.pushBack(cocos2d::CCString::create("中文"));
    }else if(learn->compare("Chinese")){
        _sources.pushBack(cocos2d::CCString::create("English"));
        _sources.pushBack(cocos2d::CCString::create("German"));
    }else{
        log("error.no learn language.");
        return false;
    }
    
    auto list = cocos2d::ui::ListView::create();
    list->setSize(Size(visibleSize.width/3*2,visibleSize.height/4));
    Size ls = list->getSize();
    list->setPosition(Vec2(visibleSize.width/2 - ls.width/2, visibleSize.height/2 - ls.height/2));
    list->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
    list->setItemsMargin(5);
    this->addChild(list);
    
    for (int i = 0 ; i < _sources.size(); i++) {
        cocos2d::CCString *s = _sources.at(i);
        auto *textbt = cocos2d::ui::Button::create("blue.png","gray.png");
        textbt->ignoreContentAdaptWithSize(false);
        textbt->setSize(Size(visibleSize.width/2,visibleSize.height/8));
        textbt->setTitleText(s->getCString());
        textbt->setTag(i);
        textbt->setTitleFontSize(40);
        textbt->setScale9Enabled(true);
        textbt->addTouchEventListener([this](Ref* p, cocos2d::ui::Widget::TouchEventType t){
            if (t == ui::Widget::TouchEventType::ENDED) {
                cocos2d::ui::Button *bt =(cocos2d::ui::Button*) p;
                
                cocos2d::CCString *se = _sources.at(bt->getTag());
                cocos2d::CCString *model = cocos2d::CCString::createWithFormat("%s_%s",this->tolearn->getCString(),se->getCString());
                
                cocos2d::CCDictionary *dic = cocos2d::CCDictionary::create();
                dic->setObject(model, "model");
                dic->setObject(this->tolearn, "learn");
                
                auto tran =  TransitionSlideInR::create(0.3, ChooseModelScene::createScene(dic));
                Director::getInstance()->replaceScene(tran);
            }
        });
        list->pushBackCustomItem(textbt);
    }
    
    this->setTolearn(learn);
    
    cocos2d::ui::Button *bt = cocos2d::ui::Button::create("back.png");
    bt->addTouchEventListener([](Ref*,cocos2d::ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto tran =  TransitionSlideInL::create(0.3, HelloWorld::createScene());
            Director::getInstance()->replaceScene(tran);
        }
    });
    bt->setPosition(Vec2(bt->getContentSize().width+10, visibleSize.height - bt->getContentSize().height - 10));
    this->addChild(bt);
    
    this->addChild(DeveloperInfo::DevInfoButton("devinfo.png"));
    
    return true;
}