//
//  FCCreateUnitAction.cpp
//  LHCocosFirstGame
//
//  Created by user on 15-1-14.
//
//

#include "FCCreateUnitAction.h"

void FCCreateUnitAction::initFrom(json_t *jt){
    const char *msg = json_string_value(jt);
    auto r = fcsplit(msg);
    tag = atoi(r[1].c_str());
    tx = atoi(r[2].c_str());
    ty = atoi(r[3].c_str());
}