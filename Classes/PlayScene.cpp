#include "PlayScene.h"
#include "GameOverScene.h"

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

PlayScene::~PlayScene(){
    array->release();
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

void PlayScene::genBlockLine(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float hmargin = visibleSize.width/20;
    float width = linewidth - hmargin*2;
    float heigt = visibleSize.height/10;
    float y = visibleSize.height;
    
    //    Vector<Sprite*> blockline(lineCount);
    CCArray *blockline = CCArray::create();
    for (int i = 0 ; i<lineCount; i++) {
        float x = i*linewidth + hmargin + linewidth/2;
        Sprite *block = Sprite::create("play.png", Rect(0, 0, width, heigt));
        block->setPosition(x, y);
        this->addChild(block);
        //        blockline.pushBack(block);
        blockline->addObject(block);
    }
    array->addObject(blockline);
}

static float bottomHeight = 60;

void PlayScene::update(float dt){
    for (int i = 0; i<array->count(); i++) {
        CCArray *ta =(CCArray*) array->objectAtIndex(i);
        for (int j = 0; j<ta->count(); j++) {
            Sprite *block = (Sprite*)ta->objectAtIndex(j);
            float x = block->getPosition().x;
            float y = block->getPosition().y;
            block->setPosition(x, y-dt*speed);
        }
    }
    
    CCArray *first = (CCArray*) array->objectAtIndex(0);
    Sprite *fs = (Sprite*) first->objectAtIndex(0);
    if (fs->getPosition().y<=bottomHeight+fs->getContentSize().height) {
        this->gameOver();
    }
    
    period += dt;
    if (period >= blockdt){
        period = 0;
        this->genBlockLine();
    }
}

void PlayScene::gameOver(){
    this->unscheduleUpdate();
//    unscheduleAllSelectors();
    
    auto tran =  TransitionMoveInR::create(0.3, GameOverScene::createScene(plevel));
    Director::getInstance()->replaceScene(tran);
}

void PlayScene::initWithLevel(int level){
    plevel = level;
    lineCount = level==0?3:4;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    linewidth = visibleSize.width/lineCount;
    speed = visibleSize.height/10;
    period = 0;
    blockdt = 1;
    
    auto starMenu = Menu::create(NULL);
    starMenu->setPosition(Point::ZERO);
    for (int i =0 ; i<lineCount; i++) {
        auto starMenuItem = MenuItemImage::create("play.png","play.png", CC_CALLBACK_1(PlayScene::blockClick, this));
        starMenuItem->setTag(i);
        starMenuItem->setPosition(Point(i*linewidth+linewidth/2, starMenuItem->getContentSize().height/2));
        starMenu->addChild(starMenuItem);
    }
    this->addChild(starMenu, 1);
    
    // 创建一个事件监听器类型为 OneByOne 的单点触摸
    auto listener1 = EventListenerTouchOneByOne::create();
    // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    listener1->setSwallowTouches(true);
    // 使用 lambda 实现 onTouchBegan 事件回调函数
    listener1->onTouchBegan = [this,listener1](Touch* touch, Event* event){
        // 获取事件所绑定的 target
        this->start_play();
        Director::getInstance()->getEventDispatcher()->removeEventListener(listener1);
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
}

void PlayScene::blockClick(Ref* pSender){
    MenuItemImage *item = (MenuItemImage*)pSender;
    int index = item->getTag();
    CCArray *first = (CCArray*) array->objectAtIndex(0);
    Sprite *fs = (Sprite*) first->objectAtIndex(index);
    if (fs->getParent() == nullptr) {
        this->gameOver();
    }else{
        fs->removeFromParent();
    }
    bool empty = true;
    for (int i = 0 ; i<first->count(); i++) {
        Sprite *s = (Sprite*) first->objectAtIndex(i);
        if (s->getParent()!=nullptr) {
            empty = false;
        }
    }
    if (empty) {
        array->removeObjectAtIndex(0);
    }
}

void PlayScene::start_play(){
    
    array = CCArray::create();
    array->retain();
    
    this->genBlockLine();
    
    this->scheduleUpdate();
}
