//
//  FCSkillFactory.h
//  LHCocosFirstGame
//
//  Created by user on 15-1-20.
//
//

#ifndef __LHCocosFirstGame__FCSkillFactory__
#define __LHCocosFirstGame__FCSkillFactory__

#include "FCSkill.h"

class FCSkillFactory{
public:
    static FCSkill* createFCAttack();
    static FCSkill* createFCMove();
};

#endif /* defined(__LHCocosFirstGame__FCSkillFactory__) */
