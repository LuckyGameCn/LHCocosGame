//
//  FCUnit.cpp
//  LHCocosFirstGame
//
//  Created by huji on 15-1-3.
//
//

#include "FCUnit.h"
#include "FCCalEngine.h"
USING_NS_CC;

FCUnit::FCUnit(){

}

void FCUnit::attack(FCUnit *unit){
    int damage = FCCalEngine::attack(this, unit);
    unit->healthValue -= damage;
}

void FCUnit::addBuff(FCBuff *buff){
    
}

void FCUnit::addSkill(FCSkill *skill){
    
}