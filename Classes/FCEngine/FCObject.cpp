//
//  FCObject.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-11-28.
//
//

#include "FCObject.h"
#include "PHSprite.h"
#include "FCGameLayer.h"
USING_NS_CC;
bool FCObject::init(const std::string &name,FCGameLayer *gamelayer){
    return init(name, name, gamelayer);
}

bool FCObject::init(const std::string &filename, const std::string &name,FCGameLayer *gamelayer){
//    aSprite = Sprite::createWithSpriteFrameName(filename);
    aSprite = PHSP(filename);
    aSprite->retain();
    
    this->_name = name;
    
    _gameLayer = gamelayer;
    
    return true;
}

FCGameLayer* FCObject::getGameLayer(){
    return _gameLayer;
}

const std::string& FCObject::getName(){
    return this->_name;
}

Vec2 FCObject::getDirection(){
    return _direction;
}

void FCObject::changePosition(int tx, int ty){
    _gameLayer->changePosition(this, tx, ty);
}

void FCObject::removeSelf(){
    _gameLayer->removeFCObject(this);
}

void FCObject::setDirection(Vec2 direction){
    if (direction.equals(_direction)) return;
    _direction = direction;
    float degree = CC_RADIANS_TO_DEGREES(-direction.getAngle()+M_PI/2);
    aSprite->setRotation(degree);
}