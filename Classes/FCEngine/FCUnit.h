//
//  FCUnit.h
//  LHCocosFirstGame
//
//  Created by huji on 15-1-3.
//
//

#ifndef __LHCocosFirstGame__FCUnit__
#define __LHCocosFirstGame__FCUnit__

#include "FCMoveObject.h"
#include "FCBuff.h"
#include "FCSkill.h"

class FCUnit : public FCMoveObject{
public:
    FCUnit();
    virtual ~FCUnit(){
    
    };
    
    int team;
    int controller;
    
    int baseDownAttack;
    int baseUpAttack;
    int baseDeffence;
    int baseMagicDeffence;
    int baseHeathVolume;
    int baseMagicVolume;
    
    int baseMoveVolume;
    int moveValue;
    
    void addBuff(FCBuff* buff);
    void addSkill(FCSkill* skill);
private:
    cocos2d::Vector<FCBuff*> _buffs;
    cocos2d::Vector<FCSkill*> _skills;
};

#endif /* defined(__LHCocosFirstGame__FCUnit__) */
