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
#include "cocostudio/CocoStudio.h"

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

bool SourceLanScene::initLearn(cocos2d::CCString* learn){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    std::stringstream ss;
    ss<<learn->getCString()<<".json";
    std::string s = cocos2d::FileUtils::getInstance()->getStringFromFile(ss.str());
    
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
    
    list->addEventListener([this](Ref* p, cocos2d::ui::ListView::EventType t){
        if (t == cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END) {
            cocos2d::ui::ListView *lv =(cocos2d::ui::ListView*) p;
            cocos2d::CCString *se = _sources.at(lv->getCurSelectedIndex());
            
        }
    });
    
    return true;
}