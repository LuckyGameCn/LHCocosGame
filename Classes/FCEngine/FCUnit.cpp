//
//  FCUnit.cpp
//  LHCocosFirstGame
//
//  Created by huji on 15-1-3.
//
//

#include "FCUnit.h"
#include "FCCalEngine.h"
#include "UIText.h"
USING_NS_CC;

FCUnit::FCUnit(){
}

void FCUnit::attack(FCUnit *unit,const std::function<void()>& done){
    int damage = FCCalEngine::attack(this, unit);
    unit->healthValue -= damage;
    auto dtext = ui::Text::create(StringUtils::format("%d",damage), "", 20);
    dtext->setPosition(unit->aSprite->getPosition());
    unit->aSprite->getParent()->addChild(dtext);
    auto fo = FadeOut::create(1);
    auto rs = RemoveSelf::create();
    auto sq = Sequence::create(fo,rs, NULL);
    dtext->runAction(sq);
    if (done) done();
}

cocos2d::Vector<FCSkill*> FCUnit::getSkills(){
    return _skills;
}

void FCUnit::addBuff(FCBuff *buff){
    
}

void FCUnit::addSkill(FCSkill *skill){
    skill->owner = this;
    _skills.pushBack(skill);
}