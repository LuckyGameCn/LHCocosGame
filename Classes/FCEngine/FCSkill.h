//
//  FCSkill.h
//  LHCocosFirstGame
//
//  Created by huji on 15-1-3.
//
//

#ifndef __LHCocosFirstGame__FCSkill__
#define __LHCocosFirstGame__FCSkill__

#include "cocos2d.h"
typedef enum{
    FCSkillTypeNone = 0,
} FCSkillType;

class FCSkill : public cocos2d::Ref{
public:
    FCSkillType type;
    std::string name;
    std::string icon;
};

#endif /* defined(__LHCocosFirstGame__FCSkill__) */
