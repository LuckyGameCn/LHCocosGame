//
//  FCBuff.h
//  LHCocosFirstGame
//
//  Created by huji on 15-1-3.
//
//

#ifndef __LHCocosFirstGame__FCBuff__
#define __LHCocosFirstGame__FCBuff__

#include "cocos2d.h"

class FCUnit;

class FCBuff : public cocos2d::Ref{
public:
    std::string name;
    std::string icon;
    std::function<void(FCUnit* unit)> buffLoad;
    std::function<void(FCUnit* unit)> buffUnLoad;
};

#endif /* defined(__LHCocosFirstGame__FCBuff__) */
