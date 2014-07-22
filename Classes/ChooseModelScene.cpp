//------.cpp
#include "ChooseModelScene.h"
#include "cocostudio/CocoStudio.h"
#include "UIButton.h"
#include "SourceLanScene.h"
#include "RemLan.h"

#define KEY_AL "al"
#define KEY_WORDS "words"
#define KEY_SOURCE "source"
#define KEY_SOUND "sound"
#define KEY_LEARN "learn"

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
    
    RemLan *lan = RemLan::create();
    const char *al = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(jdoc, KEY_AL);
    lan->setAl(cocos2d::CCString::create(al));
    int count = LHDICTOOL->getArrayCount_json(jdoc, KEY_WORDS);
    for (int i=0 ; i<count; i++) {
        const rapidjson::Value &tv = LHDICTOOL->getDictionaryFromArray_json(jdoc, KEY_WORDS, i);
        RemWord *word = RemWord::create();
        const char *source = LHDICTOOL->getStringValue_json(tv, KEY_SOURCE);
        const char *sound = LHDICTOOL->getStringValue_json(tv, KEY_SOUND);
        const char *learn = LHDICTOOL->getStringValue_json(tv, KEY_LEARN);
        word->setLearn(cocos2d::__String::create(learn));
        word->setSound(cocos2d::__String::create(sound));
        word->setSource(cocos2d::__String::create(source));
        lan->words.pushBack(word);
    }
    
    log("%s",al);
    
	return true;
}