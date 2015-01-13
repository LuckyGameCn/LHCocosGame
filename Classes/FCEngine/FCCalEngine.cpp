//
//  FCCalEngine.cpp
//  LHCocosFirstGame
//
//  Created by user on 15-1-4.
//
//

#include "FCCalEngine.h"

int FCCalEngine::attack(FCUnit *attacker, FCUnit *deffencer){
    float damage = 0;
    float df = deffencer->baseDeffence;
    float at = attacker->baseDownAttack;
    if (df>=0) {
        damage = (df*0.06f)/(1.0f+0.06f*df)*at;
    }else{
        float tmp = pow(0.94f, df);
        damage = (2.0f - tmp)*at;
    }
    return damage;
}