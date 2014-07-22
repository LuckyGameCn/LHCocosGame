//------.cpp
#include "ChooseModelScene.h"
#include "cocostudio/CocoStudio.h"
#include "UIButton.h"
#include "SourceLanScene.h"
USING_NS_CC;
Scene* ChooseModelScene::createScene(cocos2d::CCDictionary *dic)
{
	auto scene = Scene::create();
	auto layer = ChooseModelScene::create();
    layer->initDict(dic);
	scene->addChild(layer);
	return scene;
}

bool ChooseModelScene::initDict(cocos2d::CCDictionary *dic)
{
    cocos2d::CCString *model = (cocos2d::CCString *)dic->objectForKey("model");
    cocos2d::CCString *learn = (cocos2d::CCString *)dic->objectForKey("learn");
    
    cocos2d::ui::Button *bt = cocos2d::ui::Button::create("play.png");
    bt->addTouchEventListener([learn](Ref*,cocos2d::ui::Widget::TouchEventType){
        auto tran =  TransitionFadeDown::create(0.3, SourceLanScene::createScene(learn));
        Director::getInstance()->replaceScene(tran);
    });
    bt->setPosition(Vec2(40, 40));
    this->addChild(bt);
    
    std::stringstream ss;
    ss<<model->getCString()<<".json";
    std::string s = cocos2d::FileUtils::getInstance()->getStringFromFile(ss.str());

    rapidjson::Document jdoc;
    jdoc.Parse<0>(s.c_str());
    if (jdoc.HasParseError()) {
        log("parse json error.");
        return false;
    }
    
	return true;
}