#include "PlayScene.h"

USING_NS_CC;

Scene* PlayScene::createScene(int level)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();
    layer->initWithLevel(level);
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = LabelTTF::create("Score", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width/2-label->getContentSize().width/2,
                            origin.y + visibleSize.height/5*4 - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label);
    
    return true;
}

void PlayScene::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated){
    // 基线渲染
    glLineWidth(5.0f);//线条宽度
    DrawPrimitives::setDrawColor4B(255,0,0,255);//颜色
    Size visibleSize = Director::getInstance()->getVisibleSize();
    for (int i=0 ; i<lineCount-1; i++) {
        float x = (i+1)*linewidth;
        DrawPrimitives::drawLine(Vec2(x, 0),Vec2(x, visibleSize.height));
    }
}

void PlayScene::initWithLevel(int level){
    lineCount = level==0?3:4;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    linewidth = visibleSize.width/lineCount;
    
    // 创建一个事件监听器类型为 OneByOne 的单点触摸
    auto listener1 = EventListenerTouchOneByOne::create();
    // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    listener1->setSwallowTouches(true);
    // 使用 lambda 实现 onTouchBegan 事件回调函数
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        // 获取事件所绑定的 target
        
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener1, 1);
}
