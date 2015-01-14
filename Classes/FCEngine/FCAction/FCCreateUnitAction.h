//
//  FCCreateUnitAction.h
//  LHCocosFirstGame
//
//  Created by user on 15-1-14.
//
//

#ifndef __LHCocosFirstGame__FCCreateUnitAction__
#define __LHCocosFirstGame__FCCreateUnitAction__

#include "FCAction.h"

class FCCreateUnitAction : public FCAction{
public:
    FCCreateUnitAction(){
        this->acType = FCActionCreateUnit;
    };
    virtual void initFrom(json_t *jt) override;
    
    int tag;
    int tx;
    int ty;
};

#endif /* defined(__LHCocosFirstGame__FCCreateUnitAction__) */
