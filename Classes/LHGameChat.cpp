//
//  LHGameChat.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-12-20.
//
//

#include "LHGameChat.h"
#include "LHPomeloManager.h"
#include "LHGameChatView.h"
USING_NS_CC;

static LHPomeloManager *_chatManager = nullptr;
static LHGameChatView *_chatView = nullptr;
static int _userCount = 0;

static void refreshUserCountLabel(){
    _chatView->setTitle(StringUtils::format("----------%d-----------",_userCount));
}

ui::Button* LHGameChat::gameChatButton(){
    auto bt = ui::Button::create("q.png");
    bt->addTouchEventListener([bt](Ref *ps,ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (_chatManager==nullptr) {
                _chatManager = new LHPomeloManager();
                _chatManager->connect("2dxhuji", "huji");
                _chatManager->onEnterChannel = [bt](int status,json_t *resp){
                    int uc = 0;
                    json_t* users = json_object_get(resp,"users");
                    for (unsigned int i=0; i<json_array_size(users); i++) {
//                        json_t* val = json_array_get(users,i);
                        uc++;
                    }
                    _userCount = uc;
                    
                    if (_chatView == nullptr) {
                        float margin = 50;
                        Size vs = Director::getInstance()->getVisibleSize();
                        Vec2 vo = Director::getInstance()->getVisibleOrigin();
                        vs.width = vs.width - margin*2;
                        vs.height = vs.height - margin*2;
                        _chatView = new LHGameChatView();
                        _chatView->init(vs);
                        auto scene = Director::getInstance()->getRunningScene();
                        _chatView->setPosition(Vec2(vo.x+margin, vo.y+margin));
                        scene->addChild(_chatView);
                        _chatView->onSend = [](const std::string& content){
                            return _chatManager->send(content, "*");
                        };
                    }
                    
                    refreshUserCountLabel();
                };
                _chatManager->onMessage = [](json_t *resp){
                    if(!_chatView->isShowing()) return;
                    //{"msg": "d", "from": "huji", "target": "*"}
                    json_t *msg = json_object_get(resp, "msg");
                    json_t *from = json_object_get(resp, "from");
                    const char *fromstr = json_string_value(from);
                    _chatView->addOne(fromstr, json_string_value(msg), LHGameChat_MsgType_Left);
                };
                _chatManager->onAdd = [](json_t *resp){
                    _userCount++;
                    refreshUserCountLabel();
                    if(!_chatView->isShowing()) return;
                    json_t *user = json_object_get(resp, "user");
                    const char *userstr = json_string_value(user);
                    auto msg = StringUtils::format("%s >>",userstr);
                    _chatView->addOne( "",msg, LHGameChat_MsgType_Middle);
                };
                _chatManager->onLeave = [](json_t *resp){
                    _userCount--;
                    refreshUserCountLabel();
                    if(!_chatView->isShowing()) return;
                    json_t *user = json_object_get(resp, "user");
                    const char *userstr = json_string_value(user);
                    auto msg = StringUtils::format("%s ~~",userstr);
                    _chatView->addOne("",msg,  LHGameChat_MsgType_Middle);
                };
            }else{
                if (!_chatView->isShowing()) {
                    auto scene = Director::getInstance()->getRunningScene();
                    scene->addChild(_chatView);
                }
            }
        }
    });
    return bt;
}