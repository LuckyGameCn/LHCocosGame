#include "HelloWorldScene.h"
#include "PlayScene.h"
#include "UMShareButton.h"
#include "ThirdPartyHelper.h"
#include "UIListView.h"
#include "UIText.h"
#include "SourceLanScene.h"
#include "DeveloperInfoScence.h"

USING_NS_CC;
USING_NS_UM_SOCIAL;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

static void shareCallback(int platform, int stCode, string& errorMsg)
{
    if ( stCode == 100 )
    {
        CCLog("#### HelloWorld 开始分享");
    }
    else if ( stCode == 200 )
    {
        CCLog("#### HelloWorld 分享成功");
    }
    else
    {
        CCLog("#### HelloWorld 分享出错");
    }
    
    CCLog("platform num is : %d.", platform);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _learns.pushBack(cocos2d::CCString::create("German"));
    _learns.pushBack(cocos2d::CCString::create("English"));
    
    auto list = cocos2d::ui::ListView::create();
//    list->setBackGroundColor(Color3B::YELLOW);
//    list->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    list->setSize(Size(visibleSize.width/3*2,visibleSize.height/4));
    Size ls = list->getSize();
    list->setPosition(Vec2(visibleSize.width/2 - ls.width/2, visibleSize.height/2 - ls.height/2));
    list->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
    list->setItemsMargin(5);
    this->addChild(list);
    
    for (int i = 0 ; i < _learns.size(); i++) {
        cocos2d::CCString *s = _learns.at(i);
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
                cocos2d::CCString *se = _learns.at(bt->getTag());
                
                auto tran =  TransitionMoveInR::create(0.3, SourceLanScene::createScene(se));
                Director::getInstance()->replaceScene(tran);
            }
        });
        list->pushBackCustomItem(textbt);
    }
    
    
    this->addChild(DeveloperInfo::DevInfoButton("devinfo.png"));
    
    return true;
}

