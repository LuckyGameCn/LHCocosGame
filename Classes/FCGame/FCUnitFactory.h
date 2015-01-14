//
//  FCUnitFactory.h
//  LHCocosFirstGame
//
//  Created by huji on 15-1-3.
//
//

#ifndef __LHCocosFirstGame__FCUnitFactory__
#define __LHCocosFirstGame__FCUnitFactory__

#include "FCUnit.h"
#include "FCCreateUnitAction.h"

class FCUnitFactory{
public:
    static FCUnit* createNomalSoldier(FCCreateUnitAction *ac);
};

#endif /* defined(__LHCocosFirstGame__FCUnitFactory__) */
