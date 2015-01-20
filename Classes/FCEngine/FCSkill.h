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

//typedef enum{
//    FCSkillTypeNone = 0,
//} FCSkillType;
class FCUnit;
class FCObject;

class FCSkill : public cocos2d::Ref{
public:
//    FCSkillType type;
    std::string name;
//    std::string icon;
    
    FCUnit *owner;
    
    std::function<void()> onSkillClick;
    std::function<std::vector<cocos2d::Vec2>*()> onSkillRange;
    std::function<bool(int tx, int ty, cocos2d::Vector<FCObject *> *objs)> onDrawedRangeClick;
};

#endif /* defined(__LHCocosFirstGame__FCSkill__) */
