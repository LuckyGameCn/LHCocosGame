#include "HelloWorldScene.h"
#include "PlayScene.h"
#include "UMShareButton.h"
#include "ThirdPartyHelper.h"
#include "UIButton.h"

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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
//    auto easyLabel = LabelTTF::create("Easy", "Arial", 44);
//    easyLabel->setColor(Color3B::BLACK);
//    auto easyItem = MenuItemLabel::create(easyLabel, CC_CALLBACK_1(HelloWorld::testClick, this));
//    easyItem->setTag(0);
//    easyItem->setPosition(visibleSize.width/2, visibleSize.height/10*6);
//    
//    auto hardLabel = LabelTTF::create("SubmitScore", "Arial", 44);
//    hardLabel->setColor(Color3B::BLACK);
//    auto hardItem = MenuItemLabel::create(hardLabel, CC_CALLBACK_1(HelloWorld::testClick, this));
//    hardItem->setTag(1);
//    hardItem->setPosition(visibleSize.width/2, visibleSize.height/10*5);
//    
//    auto hellLabel = LabelTTF::create("showLeaderBoard", "Arial", 44);
//    hellLabel->setColor(Color3B::BLACK);
//    auto hellItem = MenuItemLabel::create(hellLabel, CC_CALLBACK_1(HelloWorld::testClick, this));
//    hellItem->setTag(2);
//    hellItem->setPosition(visibleSize.width/2, visibleSize.height/10*4);
//    
//    // 创建分享按钮, 参数1为按钮正常情况下的图片, 参数2为按钮选中时的图片,参数3为友盟appkey, 参数4为分享回调
//    UMShareButton *shareButton = UMShareButton::create("play.png","play.png", "你的友盟appkey", share_selector(shareCallback)) ;
//    // 显示在友盟分享面板上的平台
//    vector<int>* platforms = new vector<int>();
//    platforms->push_back(SINA);
//    platforms->push_back(QZONE) ;
//    platforms->push_back(QQ) ;
//    // 设置友盟分享面板上显示的平台
//    shareButton->setPlatforms(platforms);
//    // 设置文本分享内容
//    shareButton->setShareContent("umeng social cocos2d-x sdk.") ;
//    // 设置要分享的图片, 图片支持本地图片和url图片, 但是url图片必须以http://或者https://开头
//    shareButton->setShareImage("/sdcard/header.jpeg") ;
//    // 设置按钮的位置
//    shareButton->setPosition(Vec2(visibleSize.width/2, 180));
//
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(easyItem,hardItem,hellItem,shareButton, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu);

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Touchy", "Arial", 64);
    label->setColor(Color3B::BLACK);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width/2,
                            origin.y + visibleSize.height/5*4 - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label);
    
    cocos2d::ui::Button *bt = cocos2d::ui::Button::create();
    bt->setEnabled(true);
    bt->setScale(3);
    bt->setTitleText("testButton");
    bt->addTouchEventListener([](Ref*,cocos2d::ui::Widget::TouchEventType){
        log("button");
    });
    bt->setPosition(Vec2(120, 160));
    this->addChild(bt);
    
    return true;
}

static void toPlay(int level){
    auto tran =  TransitionMoveInR::create(0.3, PlayScene::createScene(level));
    Director::getInstance()->replaceScene(tran);
}

void HelloWorld::testClick(Ref *pSender){
    MenuItemLabel *l = (MenuItemLabel*)pSender;
    if (l->getTag()==1) {
        ThirdPartyHelper::uploadScore(88);
    }else if (l->getTag()==2){
        ThirdPartyHelper::showLeaderBoard();
    }
}

