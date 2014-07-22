//
//  RemWord.h
//  LHCocosFirstGame
//
//  Created by huji on 7/22/14.
//
//

#ifndef __LHCocosFirstGame__RemWord__
#define __LHCocosFirstGame__RemWord__

#include "cocos2d.h"
class RemWord : public cocos2d::Ref{
public:
    bool init();
    
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCString*, source, Source);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCString*, learn, Learn);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCString*, sound, Sound);
    
    virtual ~RemWord();
    
    CREATE_FUNC(RemWord);
};

#endif /* defined(__LHCocosFirstGame__RemWord__) */
