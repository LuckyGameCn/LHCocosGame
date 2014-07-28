#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "ChooseModelScene.h"
#include "LHPauseScene.h"
#include "LHMacro.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    UserDefault *ud = UserDefault::getInstance();
    std::string learn = ud->getStringForKey(User_Key_Learn,"");
    std::string model = ud->getStringForKey(User_Key_Model,"");
    
    if (learn.empty()) {
        // create a scene. it's an autorelease object
        auto scene = HelloWorld::createScene();
        
        // run
        director->runWithScene(scene);
    }else{
        // create a scene. it's an autorelease object
        CCDictionary *dic = CCDictionary::create();
        dic->setObject(CCString::create(learn), "learn");
        dic->setObject(CCString::create(model), "model");
        auto scene = ChooseModelScene::createScene(dic);
        
        // run
        director->runWithScene(scene);
    }
    

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    
    int sceneTag = Director::getInstance()->getRunningScene()->getTag();
    if (sceneTag > 0) {
        Director::getInstance()->pushScene(LHPauseScene::createScene(nullptr));
    }
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
