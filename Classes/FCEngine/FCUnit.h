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
    
    int baseDownAttack=10;
    int baseUpAttack=20;
    int baseDeffence=5;
    int baseMagicDeffence=10;
    int baseHealthVolume=500;
    int healthValue=baseHealthVolume;
    int baseMagicVolume=300;
    int magicValue=baseMagicVolume;
    int baseAttackRange=3;
    
    int baseMoveVolume=10;
    int actionValue=baseMoveVolume;
    
    void addBuff(FCBuff* buff);
    void addSkill(FCSkill* skill);
    cocos2d::Vector<FCSkill*> getSkills();
    
    //action
    void attack(FCUnit *unit,const std::function<void()>& done);
private:
    cocos2d::Vector<FCBuff*> _buffs;
    cocos2d::Vector<FCSkill*> _skills;
};

#endif /* defined(__LHCocosFirstGame__FCUnit__) */
