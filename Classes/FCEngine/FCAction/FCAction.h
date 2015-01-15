//
//  FCAction.h
//  LHCocosFirstGame
//
//  Created by user on 15-1-13.
//
//

#ifndef __LHCocosFirstGame__FCAction__
#define __LHCocosFirstGame__FCAction__

#include "cocos2d.h"
#include "jansson.h"

static //[0]is type.start from [1]
std::vector<std::string> fcsplit(const std::string& str)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    const std::string pattern = "#";
    int size=str.size();
    
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

typedef enum {
    FCActionNone,
    FCActionCreateUnit,
    FCActionMove,
    FCActionControl,
    FCActionAttack,
    FCActionShowUI,
}FCActionType;

class FCAction : public cocos2d::Ref{
public:
    FCAction():acType(FCActionNone){
    };
    
    FCActionType acType;
    
    virtual void initFrom(json_t *jt){};
};

#endif /* defined(__LHCocosFirstGame__FCAction__) */
