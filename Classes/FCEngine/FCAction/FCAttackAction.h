//
//  FCAttackAction.h
//  LHCocosFirstGame
//
//  Created by user on 15-1-14.
//
//

#ifndef __LHCocosFirstGame__FCAttackAction__
#define __LHCocosFirstGame__FCAttackAction__

#include "FCAction.h"

class FCAttackAction : public FCAction{
public:
    virtual void initFrom(json_t *jt) override;
};

#endif /* defined(__LHCocosFirstGame__FCAttackAction__) */
