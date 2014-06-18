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
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
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
    
    this->firsttouch = true;
    memset(touchrecord, -1, TRCOUNT*sizeof(int));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = LabelTTF::create("Score", "Arial", 24);
    label->setColor(Color3B::BLACK);
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label,1);
    scoreLabel = label;
    
//    Sprite *collect = Sprite::create("play.png", Rect(0, 0, visibleSize.width/5, visibleSize.height/10));
//    collect->setPosition(visibleSize.width/2, collect->getContentSize().height/2);
//    this->addChild(collect, 1);
//    auto ls = EventListenerTouchOneByOne::create();
//    // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
//    ls->setSwallowTouches(true);
//    
//    ls->onTouchBegan =  [this](Touch* touch, Event* event){
//        return true;
//    };
//    ls->onTouchEnded =  [this](Touch* touch, Event* event){
//        log("collect");
//        if (this->firsttouch) {
//            return;
//        }
//        int touches[TRCOUNT];
//        int ii = 0;
//        for (int i = 0 ; i<TRCOUNT; i++) {
//            if (touchrecord[i] == 1) {
//                touches[ii] = i;
//                ii ++;
//            }
//        }
//        this->blockClick(touches,lineCount);
//        memset(touchrecord, -1, TRCOUNT);
//    };
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ls, collect);
    
    auto hardItem = MenuItemImage::create("play.png", "play.png", CC_CALLBACK_1(PlayScene::collect, this));
    hardItem->setPosition(visibleSize.width/2, hardItem->getContentSize().height/2);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(hardItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}

void PlayScene::collect(cocos2d::Ref *pSender){
    int touches[TRCOUNT];
    int ii = 0;
    for (int i = 0 ; i<TRCOUNT; i++) {
        if (touchrecord[i] == 1) {
            touches[ii] = i;
            ii ++;
        }
    }
    if (ii==0) {
        memset(touchrecord, -1, TRCOUNT*sizeof(int));
        return;
    }else{
        this->blockClick(touches,ii);
        memset(touchrecord, -1, TRCOUNT*sizeof(int));
    }
}

void PlayScene::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated){
    // 基线渲染
    glLineWidth(5.0f);//线条宽度
    DrawPrimitives::setDrawColor4B(0,0,0,255);//颜色
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
    
    //    Vector<Sprite*> blockline(lineCount);
    CCArray *blockline = CCArray::create();
    for (int i = 0 ; i<lineCount; i++) {
        int tag = (int)(CCRANDOM_0_1() * lineCount);
        float x = i*linewidth + linewidth/2;
        char fnc[10];
        sprintf(fnc, "block%d.png",tag);
        std::string fn(fnc);
        Sprite *block = Sprite::create(fn, Rect(0, 0, width, heigt));
        float y = visibleSize.height+heigt;
        block->setPosition(x, y);
        block->setTag(tag);
        this->addChild(block, 0);
//        this->addChild(block);
        //        blockline.pushBack(block);
        blockline->addObject(block);
    }
    array->addObject(blockline);
}

//static float bottomHeight = 60;

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
    if (fs->getPosition().y<=fs->getContentSize().height) {
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
    lineCount = level;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    linewidth = visibleSize.width/lineCount;
    speed = visibleSize.height/10;
    period = 0;
    blockdt = 1;
    score = 0;
    
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

void PlayScene::blockClick(int tag[],int len){
//    MenuItemImage *item = (MenuItemImage*)pSender;
//    int index = item->getTag();
    int rmtag = 0;
    CCArray *first = (CCArray*) array->objectAtIndex(0);
    for (int ii = 0; ii<len; ii++) {
        int t = tag[ii];
        Sprite *fs = (Sprite*) first->objectAtIndex(t);
        if (fs->getParent() == nullptr) {
            this->gameOver();
            return;
        }else{
            score++;
            fs->removeFromParent();
            rmtag = fs->getTag();
        }
        for (int j = ii+1; j<len; j++) {
            int tt = tag[j];
            Sprite *ofs = (Sprite*) first->objectAtIndex(tt);
            if (fs->getTag() != ofs->getTag()) {
                this->gameOver();
                return;
            }
        }
    }
    
    bool empty = true;
    for (int i = 0 ; i<first->count(); i++) {
        Sprite *s = (Sprite*) first->objectAtIndex(i);
        if (s->getParent()!=nullptr) {
            empty = false;
            
            if (s->getTag()==rmtag) {
                this->gameOver();
                return;
            }
        }
    }
    if (empty) {
        array->removeObjectAtIndex(0);
    }
    
    char scc[10];
    sprintf(scc, "%d",(int)score);
    std::string sc(scc);
    scoreLabel->setString(sc);
}

void PlayScene::clickline(int line,int state){
     CCArray *first = (CCArray*) array->objectAtIndex(0);
    Sprite *sp = (Sprite*)first->objectAtIndex(line);
    
    if (state == 1) {
        ScaleTo *stos = ScaleTo::create(0.02, 0.9);
        ScaleTo *stob = ScaleTo::create(0.1, 1.5);
        Sequence *sq = Sequence::create(stos,stob, NULL);
        sp->runAction(sq);
    }else{
        ScaleTo *stos = ScaleTo::create(0.1, 1.0);
        ScaleTo *stob = ScaleTo::create(0.02, 1.6);
        Sequence *sq = Sequence::create(stob,stos, NULL);
        sp->runAction(sq);
    }
}

void PlayScene::start_play(){
    
    array = CCArray::create();
    array->retain();
    
    this->genBlockLine();
    
    this->scheduleUpdate();
    
    auto ls = EventListenerTouchOneByOne::create();
    ls->onTouchBegan = [this](Touch *touch,Event *event){
        return true;
    };
    ls->onTouchEnded = [this](Touch *touch,Event *event){
//        if(this->firsttouch){
//            this->firsttouch = false;
//            return;
//        }
//        int touchTag[touches.size()];
//        memset(touchTag, -1, touches.size());
//        for (int i = 0; i<touches.size(); i++) {
//            Touch *touch = touches.at(i);
        int tag = (int)(touch->getLocation().x / linewidth);
        touchrecord[tag] *= -1;
        this->clickline(tag,touchrecord[tag]);
//            touchTag[i]=tag;
//        }
//        this->blockClick(touchTag,touches.size());
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ls, this);
}
