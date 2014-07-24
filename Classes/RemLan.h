//
//  RemLan.h
//  LHCocosFirstGame
//
//  Created by huji on 7/22/14.
//
//

#ifndef __LHCocosFirstGame__RemLan__
#define __LHCocosFirstGame__RemLan__

#include "cocos2d.h"
#include "RemWord.h"
class RemLan : public cocos2d::Ref
{
public:
    bool init();
    
    virtual ~RemLan();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::__String*,al,Al);
    cocos2d::Vector<RemWord*> words;
    
    CREATE_FUNC(RemLan);
};

#endif /* defined(__LHCocosFirstGame__RemLan__) */
