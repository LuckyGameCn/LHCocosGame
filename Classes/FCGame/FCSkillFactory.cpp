//
//  FCSkillFactory.cpp
//  LHCocosFirstGame
//
//  Created by user on 15-1-20.
//
//

#include "FCSkillFactory.h"
#include "FCUnit.h"
#include "FCGameLayer.h"
USING_NS_CC;

FCSkill* FCSkillFactory::createFCAttack(){
    auto skill = new FCSkill();
    skill->autorelease();
    skill->name="Attack";
    skill->onSkillClick=[skill](){
        auto gl = skill->owner->getGameLayer();
        gl->drawRange(skill, "lgreenback.png");
    };
    skill->onSkillRange=[skill](){
        std::vector<Vec2> *range = new std::vector<Vec2>;
        auto gl = skill->owner->getGameLayer();
        gl->enumerateMap([range,skill](int tx, int ty, cocos2d::Vector<FCObject *> *){
            if (tx==skill->owner->tx||ty==skill->owner->ty) {
                range->push_back(Vec2(tx, ty));
            }
            return true;
        });
        return range;
    };
    skill->onDrawedRangeClick=[skill](int tx, int ty, cocos2d::Vector<FCObject *> *objs){
        if (objs->size()==0) {
            return false;
        }
        
        skill->owner->attack((FCUnit*)objs->at(0), [skill](){
            skill->owner->clickEnable=true;
        });
        skill->owner->clickEnable=false;
        
        return true;
    };
    return skill;
}

FCSkill* FCSkillFactory::createFCMove(){
    auto skill = new FCSkill();
    skill->autorelease();
    skill->name="Move";
    skill->onSkillClick=[skill](){
        auto gl = skill->owner->getGameLayer();
        gl->drawRange(skill, "lgreenback.png");
    };
    skill->onSkillRange=[skill](){
        std::vector<Vec2> *range = new std::vector<Vec2>;
        auto gl = skill->owner->getGameLayer();
        gl->enumerateMap([range,skill](int tx, int ty, cocos2d::Vector<FCObject *> *){
            if (tx==skill->owner->tx||ty==skill->owner->ty) {
                range->push_back(Vec2(tx, ty));
            }
            return true;
        });
        return range;
    };
    skill->onDrawedRangeClick=[skill](int tx, int ty, cocos2d::Vector<FCObject *> *objs){
        if (objs->size()>0) {
            return false;
        }
        
        skill->owner->getGameLayer()->move(skill->owner, tx, ty);
        skill->owner->onMoveEnd=[skill](){
            skill->owner->clickEnable=true;
        };
        skill->owner->clickEnable=false;
        
        return true;
    };
    return skill;
}

