//
//  FCAction.h
//  LHCocosFirstGame
//
//  Created by user on 15-1-13.
//
//

#ifndef __LHCocosFirstGame__FCAction__
#define __LHCocosFirstGame__FCAction__

#include "cocos2d.h"

typedef enum {
    FCActionMove,
}FCActionType;

class FCAction : public cocos2d::Ref{
public:
    FCActionType acType;
};

#endif /* defined(__LHCocosFirstGame__FCAction__) */
