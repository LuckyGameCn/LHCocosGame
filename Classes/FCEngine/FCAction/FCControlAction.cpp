//
//  FCControlAction.cpp
//  LHCocosFirstGame
//
//  Created by user on 15-1-14.
//
//

#include "FCControlAction.h"

void FCControlAction::initFrom(json_t *jt){
    const char *msg = json_string_value(jt);
    auto r = fcsplit(msg);
    
}