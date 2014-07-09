#include "DeveloperInfoScence.h"

USING_NS_CC;

Scene* DeveloperInfo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = DeveloperInfo::create();
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool DeveloperInfo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create menu, it's an autorelease object
//    auto menu = Menu::create(easyItem,hardItem,hellItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu);

    /////////////////////////////
    // 3. add your codes below...

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
    
    return true;
}
