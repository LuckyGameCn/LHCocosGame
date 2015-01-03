//
//  FCObject.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-11-28.
//
//

#include "FCObject.h"
#include "FCGameManager.h"
#include "PHSprite.h"
USING_NS_CC;
bool FCObject::init(const std::string &name){
    return init(name, name);
}

bool FCObject::init(const std::string &filename, const std::string &name){
//    aSprite = Sprite::createWithSpriteFrameName(filename);
    aSprite = PHSP(filename);
    aSprite->retain();
    
    this->_name = name;
    return true;
}

const std::string& FCObject::getName(){
    return this->_name;
}

Vec2 FCObject::getDirection(){
    return _direction;
}

void FCObject::changePosition(int tx, int ty){
    FCGameManager::getInstance()->changePosition(this, tx, ty);
}

void FCObject::removeSelf(){
    FCGameManager::getInstance()->removeFCObject(this);
}

void FCObject::setDirection(Vec2 direction){
    if (direction.equals(_direction)) return;
    _direction = direction;
    float degree = CC_RADIANS_TO_DEGREES(-direction.getAngle()+M_PI/2);
    aSprite->setRotation(degree);
}