#include "HelloWorldScene.h"
#include "PlayScene.h"

USING_NS_CC;

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
    auto easyLabel = LabelTTF::create("Easy", "Arial", 34);
    auto easyItem = MenuItemLabel::create(easyLabel, CC_CALLBACK_1(HelloWorld::easy, this));
    easyItem->setPosition(visibleSize.width/2, visibleSize.height/10*6);
    
    auto hardLabel = LabelTTF::create("Hard", "Arial", 34);
    auto hardItem = MenuItemLabel::create(hardLabel, CC_CALLBACK_1(HelloWorld::hard, this));
    hardItem->setPosition(visibleSize.width/2, visibleSize.height/10*5);
    
    auto hellLabel = LabelTTF::create("Hell", "Arial", 34);
    auto hellItem = MenuItemLabel::create(hellLabel, CC_CALLBACK_1(HelloWorld::hell, this));
    hellItem->setPosition(visibleSize.width/2, visibleSize.height/10*4);

    // create menu, it's an autorelease object
    auto menu = Menu::create(easyItem,hardItem,hellItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Touchy", "Arial", 54);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width/2,
                            origin.y + visibleSize.height/5*4 - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label);
    
    return true;
}

static void toPlay(int level){
    auto tran =  TransitionMoveInR::create(0.3, PlayScene::createScene(level));
    Director::getInstance()->replaceScene(tran);
}

void HelloWorld::hell(Ref *pSender){
    toPlay(4);
}

void HelloWorld::hard(Ref* pSender){
    toPlay(3);
}

void HelloWorld::easy(Ref* pSender){
    toPlay(2);
}

