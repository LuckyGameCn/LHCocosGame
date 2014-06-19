//
//  ThirdPartyHelper.cpp
//  LHCocosFirstGame
//
//  Created by huji on 6/19/14.
//
//

#include "ThirdPartyHelper.h"
#include "cocos2d.h"
#include "NDKHelper.h"

void ThirdPartyHelper::setAd(int tag){
    CCDictionary *dic = CCDictionary::create();
    if (tag == SET_AD_SHOW) {
        dic->setObject(CCString::create("1"), "setAd");
    }else{
        dic->setObject(CCString::create("0"), "setAd");
    }
    SendMessageWithParams("setAd", dic);
}