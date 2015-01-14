//
//  FCMoveAction.h
//  LHCocosFirstGame
//
//  Created by user on 15-1-14.
//
//

#ifndef __LHCocosFirstGame__FCMoveAction__
#define __LHCocosFirstGame__FCMoveAction__

#include "FCAction.h"

class FCMoveAction : public FCAction{
public:
    virtual void initFrom(json_t *jt) override;
};

#endif /* defined(__LHCocosFirstGame__FCMoveAction__) */
