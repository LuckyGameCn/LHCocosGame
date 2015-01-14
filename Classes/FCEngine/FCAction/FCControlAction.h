//
//  FCControlAction.h
//  LHCocosFirstGame
//
//  Created by user on 15-1-14.
//
//

#ifndef __LHCocosFirstGame__FCControlAction__
#define __LHCocosFirstGame__FCControlAction__

#include "FCAction.h"

class FCControlAction : public FCAction{
public:
    virtual void initFrom(json_t *jt) override;
};

#endif /* defined(__LHCocosFirstGame__FCControlAction__) */
