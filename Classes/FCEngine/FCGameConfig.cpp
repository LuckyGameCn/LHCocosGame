//
//  FCGameConfig.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-11-29.
//
//

#include "FCGameConfig.h"

static FCGameConfig* _instance = nullptr;

FCGameConfig* FCGameConfig::getInstance(){
    if (!_instance) {
        _instance = new FCGameConfig();
    }
    return _instance;
}