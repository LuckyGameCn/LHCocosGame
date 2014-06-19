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
    
    this->swallow = false;
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
    
    return true;
}

void PlayScene::collect(cocos2d::Ref *pSender){
    int ii = 0;
    for (int i = 0 ; i<TRCOUNT; i++) {
        if (touchrecord[i] == 1) {
            ii ++;
        }
    }
    if (ii==0) {
        memset(touchrecord, -1, TRCOUNT*sizeof(int));
        return;
    }else{
        this->blockClick(touchrecord,lineCount);
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
//    CCArray *blockline = CCArray::create();
    for (int i = 0 ; i<lineCount; i++) {
        CCArray *blockline = (CCArray*) array->objectAtIndex(i);
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
        blockline->addObject(block);
    }
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
            
            if (block->getPosition().y<=block->getContentSize().height/2) {
                this->gameOver();
                return;
            }
        }
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
    CCArray *firstafterrm = CCArray::createWithCapacity(lineCount);
    CCArray *first = CCArray::createWithCapacity(lineCount);
    for (int i = 0 ; i<len; i++) {
        int value = tag[i];
        CCArray *line = (CCArray*)array->objectAtIndex(i);
        Sprite *fb = (Sprite*)line->objectAtIndex(0);
        if (value == 1) {
            first->addObject(fb);
            line->removeObjectAtIndex(0);
        }else{
            firstafterrm->addObject(fb);
        }
    }
    
    int rmtag = 0;
    for (int ii = 0; ii<first->count(); ii++) {
        Sprite *fs = (Sprite*) first->objectAtIndex(ii);
        
        for (int j = ii+1; j<first->count(); j++) {
            Sprite *ofs = (Sprite*) first->objectAtIndex(j);
            if (fs->getTag() != ofs->getTag()) {
                this->gameOver();
                return;
            }
        }
        
        score++;
        fs->removeFromParent();
        rmtag = fs->getTag();
        ParticleSystemQuad *m_emitter = ParticleSystemQuad::create("particle.plist");
        m_emitter->setDuration(0.5);
        m_emitter->setPosition(fs->getPosition());
        m_emitter->setAutoRemoveOnFinish(true);
        this->addChild(m_emitter);
    }

    for (int i = 0 ; i<firstafterrm->count(); i++) {
        Sprite *s = (Sprite*) firstafterrm->objectAtIndex(i);
        if (s->getTag()==rmtag) {
            this->gameOver();
            return;
        }
    }
    
    char scc[10];
    sprintf(scc, "%d",(int)score);
    std::string sc(scc);
    scoreLabel->setString(sc);
}

void PlayScene::clickline(int line,int state){
    CCArray *first = (CCArray*) array->objectAtIndex(line);
    Sprite *sp = (Sprite*)first->objectAtIndex(0);
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
    
    array = CCArray::createWithCapacity(lineCount);
    array->retain();
    for (int i =0; i<lineCount; i++) {
        array->addObject(CCArray::create());
    }
    
    this->genBlockLine();
    
    this->scheduleUpdate();
    
    auto ls = EventListenerTouchOneByOne::create();
    ls->onTouchBegan = [this](Touch *touch,Event *event){
        return true;
    };
    ls->onTouchMoved = [this](Touch *touch,Event *event){
        Vec2 p = touch->getPreviousLocation();
        Vec2 c = touch->getLocation();
        float dx = p.distance(c);
        if (dx>linewidth/5) {
            this->collect(nullptr);
            this->swallow = true;
        }
    };
    ls->onTouchEnded = [this,ls](Touch *touch,Event *event){
        if(this->swallow){
            this->swallow = false;
            return;
        }
        int tag = (int)(touch->getLocation().x / linewidth);
        CCArray *first = (CCArray*) array->objectAtIndex(tag);
        if (first->count() == 0) {
            return;
        }
        
        touchrecord[tag] *= -1;
        this->clickline(tag,touchrecord[tag]);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ls, this);
}
