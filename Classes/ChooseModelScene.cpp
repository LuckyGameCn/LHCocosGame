//------.cpp
#include "ChooseModelScene.h"
#include "cocostudio/CocoStudio.h"
#include "UIButton.h"
#include "SourceLanScene.h"
#include "MemorizeScene.h"
#include "PlayScene.h"
#include "DeveloperInfoScence.h"

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

ChooseModelScene::~ChooseModelScene(){
    CC_SAFE_RELEASE(remlan);
    CC_SAFE_RELEASE(tolearn);
}

bool ChooseModelScene::initDict(cocos2d::CCDictionary *dic)
{
    cocos2d::CCString *model = (cocos2d::CCString *)dic->objectForKey("model");
    cocos2d::CCString *learn = (cocos2d::CCString *)dic->objectForKey("learn");
    
    setTolearn(learn);
    
    Size visible = Director::getInstance()->getVisibleSize();
    
    cocos2d::ui::Button *bt = cocos2d::ui::Button::create("back.png");
    bt->addTouchEventListener([learn](Ref*,cocos2d::ui::Widget::TouchEventType){
        auto tran =  TransitionMoveInR::create(0.3, SourceLanScene::createScene(learn));
        Director::getInstance()->replaceScene(tran);
    });
    bt->setPosition(Vec2(bt->getContentSize().width+10, visible.height - bt->getContentSize().height - 10));
    this->addChild(bt);
    
    this->addChild(DeveloperInfo::DevInfoButton("devinfo.png"));
    
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
    this->setRemlan(lan);
    
    cocos2d::ui::Button *memorize = cocos2d::ui::Button::create("play.png");
    memorize->ignoreContentAdaptWithSize(false);
    memorize->setSize(Size(50,30));
    memorize->setTitleFontSize(40);
    memorize->addTouchEventListener([this](Ref*,cocos2d::ui::Widget::TouchEventType type){
        if(type != ui::Widget::TouchEventType::ENDED) return;
        cocos2d::CCDictionary *dict = cocos2d::CCDictionary::create();
        dict->setObject(this->getRemlan(), "lan");
        auto tran =  TransitionFadeDown::create(0.3, MemorizeScene::createScene(dict));
        Director::getInstance()->pushScene(tran);
    });
    memorize->setPosition(Vec2(visible.width/2, 400));
    this->addChild(memorize);
    
    cocos2d::ui::Button *play = cocos2d::ui::Button::create();
    play->setColor(Color3B::BLUE);
    play->ignoreContentAdaptWithSize(false);
    play->setSize(Size(50,30));
    play->setTitleFontSize(40);
    play->setTitleText("play");
    play->addTouchEventListener([this](Ref*,cocos2d::ui::Widget::TouchEventType type){
        if(type != ui::Widget::TouchEventType::ENDED) return;
        cocos2d::CCDictionary *dict = cocos2d::CCDictionary::create();
        dict->setObject(this->getRemlan(), "lan");
        auto tran =  TransitionFadeDown::create(0.3, PlayScene::createScene(dict));
        Director::getInstance()->pushScene(tran);
    });
    play->setPosition(Vec2(visible.width/2, 300));
    this->addChild(play);
    
	return true;
}