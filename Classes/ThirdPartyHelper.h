//
//  ThirdPartyHelper.h
//  LHCocosFirstGame
//
//  Created by huji on 6/19/14.
//
//

#ifndef __LHCocosFirstGame__ThirdPartyHelper__
#define __LHCocosFirstGame__ThirdPartyHelper__

#include <iostream>

#define SET_AD_SHOW 1
#define SET_AD_HID 0

class ThirdPartyHelper{
public:
    static void setAd(int tag);
    static void uploadScore(int score);
    static void showLeaderBoard();
};

#endif /* defined(__LHCocosFirstGame__ThirdPartyHelper__) */
