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

USING_NS_CC;

Scene* SourceLanScene::createScene(cocos2d::CCString* learn)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SourceLanScene::create();
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
    list->setSize(Size(visibleSize.width/3*2,visibleSize.height/5*4));
    Size ls = list->getSize();
    list->cocos2d::Node::setPosition(visibleSize.width/2 - ls.width/2, visibleSize.height/2 - ls.height/2);
    this->addChild(list);
    
    for (int i = 0 ; i < _sources.size(); i++) {
        cocos2d::CCString *s = _sources.at(i);
        cocos2d::ui::Text *text = cocos2d::ui::Text::create(s->getCString(), "Arial", 60);
        text->setTextHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        list->pushBackCustomItem(text);
    }
    
    this->setTolearn(learn);
    list->addEventListener([this](Ref* p, cocos2d::ui::ListView::EventType t){
        if (t == cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END) {
            cocos2d::ui::ListView *lv =(cocos2d::ui::ListView*) p;
            cocos2d::CCString *se = _sources.at(lv->getCurSelectedIndex());
            cocos2d::CCString *model = cocos2d::CCString::createWithFormat("%s_%s",this->tolearn->getCString(),se->getCString());
            
            cocos2d::CCDictionary *dic = cocos2d::CCDictionary::create();
            dic->setObject(model, "model");
            dic->setObject(this->tolearn, "learn");
            
            auto tran =  TransitionFadeDown::create(0.3, ChooseModelScene::createScene(dic));
            Director::getInstance()->replaceScene(tran);
        }
    });
    
    cocos2d::ui::Button *bt = cocos2d::ui::Button::create("play.png");
    bt->addTouchEventListener([](Ref*,cocos2d::ui::Widget::TouchEventType){
        auto tran =  TransitionFadeDown::create(0.3, HelloWorld::createScene());
        Director::getInstance()->replaceScene(tran);
    });
    bt->setPosition(Vec2(40, 40));
    this->addChild(bt);
    
    return true;
}