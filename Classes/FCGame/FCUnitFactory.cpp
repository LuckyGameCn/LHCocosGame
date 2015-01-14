//
//  FCUnitFactory.cpp
//  LHCocosFirstGame
//
//  Created by huji on 15-1-3.
//
//

#include "FCUnitFactory.h"

FCUnit* FCUnitFactory::createNomalSoldier(FCCreateUnitAction *ac){
    auto unit = new FCUnit();
    unit->autorelease();
    unit->init("sodlier");
    unit->tag=ac->tag;
    unit->tx=ac->tx;
    unit->ty=ac->ty;
    return unit;
}