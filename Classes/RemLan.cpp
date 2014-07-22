//
//  RemLan.cpp
//  LHCocosFirstGame
//
//  Created by huji on 7/22/14.
//
//

#include "RemLan.h"

bool RemLan::init(){
    al = nullptr;
    return true;
}

RemLan::~RemLan(){
    CC_SAFE_RELEASE(al);
}