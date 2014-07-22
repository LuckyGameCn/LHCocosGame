//
//  RemWord.cpp
//  LHCocosFirstGame
//
//  Created by huji on 7/22/14.
//
//

#include "RemWord.h"

bool RemWord::init(){
    sound = nullptr;
    source = nullptr;
    learn = nullptr;
    return true;
}

RemWord::~RemWord(){
    CC_SAFE_RELEASE(sound);
    CC_SAFE_RELEASE(source);
    CC_SAFE_RELEASE(learn);
}