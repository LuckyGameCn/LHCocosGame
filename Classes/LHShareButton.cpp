//
//  LHShareButton.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-7-30.
//
//

#include "LHShareButton.h"

USING_NS_UM_SOCIAL;

#define CurrentScreen "cuurentscreen.png"
#define UMAppKey "appkey"

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

LHShareButton::LHShareButton(){
    
}

LHShareButton* LHShareButton::defaultButton(const char *shareText){
    auto bt = LHShareButton::create("share.png", "", UMAppKey, share_selector(shareCallback));
    return bt;
}

LHShareButton* LHShareButton::create(const char *normalImage, const char *selectedImage, const char *umAppKey, umeng::social::ShareEventHandler callback){
    auto bt = LHShareButton::create();
    bt->init(normalImage,selectedImage);
    bt->setShareCallback(callback);
    bt->initWithAppKey(umAppKey);
    
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
    platforms->push_back(RENREN) ;
    platforms->push_back(DOUBAN) ;
    platforms->push_back(QZONE) ;
    platforms->push_back(QQ) ;
    // 设置友盟分享面板上显示的平台
    bt->setPlatforms(platforms);
    
    bt->addTouchEventListener([bt](Ref*node,ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            Size vs = Director::getInstance()->getVisibleSize();
            RenderTexture *rd = RenderTexture::create(vs.width, vs.height);
            rd->begin();
            Director::getInstance()->getRunningScene()->visit();
            rd->end();
            
            rd->saveToFile(CurrentScreen,Image::Format::PNG);
            
            bt->mSocialSDK->openShare(bt->mShareText.c_str(), CurrentScreen, bt->mCallback);
        }
    });
    
    return bt;
}

void LHShareButton::setShareContent(const char* text) {
	if (text != NULL) {
		this->mShareText = text;
	}
}

void LHShareButton::initWithAppKey(const char *umAppKey){
    mSocialSDK = umeng::social::CCUMSocialSDK::create(umAppKey);
}

void LHShareButton::setShareCallback(umeng::social::ShareEventHandler callback){
    mCallback = callback;
}

void LHShareButton::setPlatforms(vector<int>* platforms) {
	if (mSocialSDK != NULL) {
		mSocialSDK->setPlatforms(platforms);
	}
}