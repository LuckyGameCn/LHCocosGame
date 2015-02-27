//
//  LHShareButton.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-7-30.
//
//

#include "LHShareButton.h"
#include "LHMacros.h"

USING_NS_CC;

#define CurrentScreen "cuurentscreen.png"

LHShareButton::LHShareButton(){
    
}

LHShareButton* LHShareButton::defaultButton(const char *normal,const char *shareText){
    auto bt = LHShareButton::create(normal, "");
    bt->setShareContent(shareText);
    return bt;
}

LHShareButton* LHShareButton::create(const char *normalImage, const char *selectedImage){
    auto bt = LHShareButton::create();
    
    bt->addTouchEventListener([bt](Ref*node,ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            Size vs = Director::getInstance()->getVisibleSize();
            RenderTexture *rd = RenderTexture::create(vs.width, vs.height);
            rd->begin();
            Director::getInstance()->getRunningScene()->visit();
            rd->end();
            
            rd->saveToFile(CurrentScreen,Image::Format::PNG);
            
            std::string fp = StringUtils::format("%s%s",FileUtils::getInstance()->getWritablePath().c_str(),CurrentScreen);
           
        }
    });
    
    return bt;
}

void LHShareButton::setShareContent(const char* text) {
	if (text != NULL) {
		this->mShareText = text;
	}
}