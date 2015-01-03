//
//  FCUnitFactory.cpp
//  LHCocosFirstGame
//
//  Created by huji on 15-1-3.
//
//

#include "FCUnitFactory.h"

FCUnit* FCUnitFactory::createNomalSoldier(){
    auto unit = new FCUnit();
    unit->autorelease();
    unit->init("sodlier");
    unit->baseMoveVolume = 5;
    unit->moveValue = 5;
    return unit;
}