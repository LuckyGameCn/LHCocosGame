//
//  LHLeaderBoard.cpp
//  LHCocosFirstGame
//
//  Created by huji on 7/30/14.
//
//

#include "LHLeaderBoard.h"
#include "ThirdPartyHelper.h"

cocos2d::ui::Button* LHLeaderBoard::defaultButton(){
    auto bt = cocos2d::ui::Button::create("leaderboard.png");
    bt->addTouchEventListener([](cocos2d::Ref* ps,cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            ThirdPartyHelper::showLeaderBoard();
        }
    });
    return bt;
}