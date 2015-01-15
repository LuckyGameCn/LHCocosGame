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
    FCControlAction(){
        this->acType = FCActionControl;
    };
    virtual void initFrom(json_t *jt) override;
    
    int ttag;
};

#endif /* defined(__LHCocosFirstGame__FCControlAction__) */
