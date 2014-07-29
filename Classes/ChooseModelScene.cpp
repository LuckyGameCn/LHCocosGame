//------.cpp
#include "ChooseModelScene.h"
#include "cocostudio/CocoStudio.h"
#include "UIButton.h"
#include "SourceLanScene.h"
#include "MemorizeScene.h"
#include "PlayScene.h"
#include "DeveloperInfoScence.h"
#include "LocalizedString.h"
#include "LHMacro.h"
#include "LHShareButton.h"

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
    layer->initWithColor(Color4B::WHITE);
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
    
    UserDefault *ud = UserDefault::getInstance();
    ud->setStringForKey(User_Key_Learn, std::string(learn->getCString()));
    ud->setStringForKey(User_Key_Model, std::string(model->getCString()));
    ud->flush();
    
    setTolearn(learn);
    
    Size visible = Director::getInstance()->getVisibleSize();
    
    cocos2d::ui::Button *bt = cocos2d::ui::Button::create("back.png");
    bt->addTouchEventListener([learn](Ref*,cocos2d::ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED){
        auto tran =  TransitionSlideInL::create(0.3, SourceLanScene::createScene(learn));
        Director::getInstance()->replaceScene(tran);
        }
    });
    bt->setPosition(Vec2(bt->getContentSize().width+10, visible.height - bt->getContentSize().height - 10));
    this->addChild(bt);
    
    ui::Button *infobt = DeveloperInfo::DevInfoButton("devinfo.png");
    this->addChild(infobt);
    
    LHShareButton *sharebt = LHShareButton::defaultButton("Memorize");
    sharebt->setPosition(Vec2(infobt->getPosition().x - infobt->getContentSize().width - 30, infobt->getPosition().y));
    this->addChild(sharebt);
    
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
    
    cocos2d::ui::Button *memorize = cocos2d::ui::Button::create("blue.png","gray.png");
    memorize->ignoreContentAdaptWithSize(false);
    memorize->setScale9Enabled(true);
    memorize->setSize(Size(visible.width/2,visible.height/8));
    memorize->setTitleFontSize(40);
    memorize->setTitleText(LHLocalizedCString("memorize"));
    memorize->addTouchEventListener([this](Ref*,cocos2d::ui::Widget::TouchEventType type){
        if(type != ui::Widget::TouchEventType::ENDED) return;
        cocos2d::CCDictionary *dict = cocos2d::CCDictionary::create();
        dict->setObject(this->getRemlan(), "lan");
        auto tran =  TransitionSlideInR::create(0.3, MemorizeScene::createScene(dict));
        Director::getInstance()->pushScene(tran);
    });
    memorize->setPosition(Vec2(visible.width/2, visible.height/2 + memorize->getContentSize().height));
    this->addChild(memorize);
    
    cocos2d::ui::Button *play = cocos2d::ui::Button::create("blue.png","gray.png");
    play->ignoreContentAdaptWithSize(false);
    play->setSize(Size(visible.width/2,visible.height/8));
    play->setTitleFontSize(40);
    play->setScale9Enabled(true);
    play->setTitleText(LHLocalizedCString("crossword"));
    play->addTouchEventListener([this](Ref*,cocos2d::ui::Widget::TouchEventType type){
        if(type != ui::Widget::TouchEventType::ENDED) return;
        cocos2d::CCDictionary *dict = cocos2d::CCDictionary::create();
        dict->setObject(this->getRemlan(), "lan");
        auto tran =  TransitionSlideInR::create(0.3, PlayScene::createScene(dict));
        Director::getInstance()->pushScene(tran);
    });
    play->setPosition(Vec2(visible.width/2, visible.height/2 - play->getContentSize().height));
    this->addChild(play);
    
	return true;
}