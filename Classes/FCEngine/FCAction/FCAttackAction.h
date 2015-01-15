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
    FCAttackAction(){
        this->acType=FCActionAttack;
    };
    virtual void initFrom(json_t *jt) override;
    
    int ftag;
    int ttag;
};

#endif /* defined(__LHCocosFirstGame__FCAttackAction__) */
