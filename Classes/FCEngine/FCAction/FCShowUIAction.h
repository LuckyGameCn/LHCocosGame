//
//  FCShowUIAction.h
//  LHCocosFirstGame
//
//  Created by user on 15-1-14.
//
//

#ifndef __LHCocosFirstGame__FCShowUIAction__
#define __LHCocosFirstGame__FCShowUIAction__

#include "FCAction.h"

class FCShowUIAction : public FCAction{
public:
    virtual void initFrom(json_t *jt) override;
};

#endif /* defined(__LHCocosFirstGame__FCShowUIAction__) */
