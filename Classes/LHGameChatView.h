//
//  LHGameChatView.h
//  LHCocosFirstGame
//
//  Created by huji on 14-12-20.
//
//

#ifndef __LHCocosFirstGame__LHGameChatView__
#define __LHCocosFirstGame__LHGameChatView__

#include "cocos2d.h"
#include "UILayout.h"
#include "UIListView.h"
#include "UIText.h"

#define LHGameChat_MsgType_Left 0
#define LHGameChat_MsgType_Right 1

class LHGameChatView : public cocos2d::ui::Layout{
public:
    virtual bool init(cocos2d::Size size);
    
    void setTitle(const std::string& title);
    void addOne(const std::string& username,const std::string& msgstr,int type);
    void clearMessage();
    void disMiss();
    
    bool isShowing();
private:
    cocos2d::ui::Text *_titleView;
    cocos2d::ui::ListView *_messageListView;
};

#endif /* defined(__LHCocosFirstGame__LHGameChatView__) */
