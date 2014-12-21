//
//  LHGameChatView.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-12-20.
//
//

#include "LHGameChatView.h"
#include "LHMacros.h"
#include "UIButton.h"
USING_NS_CC;
bool LHGameChatView::init(cocos2d::Size size){
    if (!Layout::init()) {
        return false;
    }
    
    setSize(size);
    
    _titleView = ui::Text::create("--", Common_Font, 30);
    _titleView->setPosition(Vec2(size.width/2, size.height-_titleView->getContentSize().height/2));
    _titleView->setColor(Color3B::GRAY);
    addChild(_titleView);
    
    _messageListView = ui::ListView::create();
    _messageListView->setSize(Size(size.width, size.height - _titleView->getContentSize().height));
    _messageListView->setPosition(Vec2(0, 0));
//    _messageListView->setBackGroundImage("phsprite.png");
//    _messageListView->setBackGroundImageScale9Enabled(true);
    addChild(_messageListView);
    
    auto backbt = ui::Button::create("q.png");
    backbt->setPosition(Vec2(0, size.height));
    backbt->addTouchEventListener([this](Ref *ps,ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->disMiss();
        }
    });
    addChild(backbt);
    
    setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    setBackGroundColor(Color3B::BLACK);
    setBackGroundColorOpacity(200);
    
    return true;
}

void LHGameChatView::disMiss(){
    clearMessage();
    removeFromParent();
}

void LHGameChatView::clearMessage(){
    _messageListView->removeAllItems();
}

bool LHGameChatView::isShowing(){
    return !(getParent()==nullptr);
}

void LHGameChatView::addOne(const std::string &username, const std::string &msgstr, int type){
    float margin = 5;
    auto lo = ui::Layout::create();
    auto msgt  = ui::Text::create(msgstr, Common_Font, 35);
    msgt->setPosition(Vec2(getSize().width/2, margin+msgt->getContentSize().height/2));
    auto unt = ui::Text::create(username, Common_Font, 30);
    unt->setPosition(Vec2(getSize().width/2, margin*2+msgt->getContentSize().height+unt->getContentSize().height/2));
    lo->setSize(Size(getSize().width, unt->getContentSize().height+msgt->getContentSize().height+margin*3));
    lo->addChild(unt);
    lo->addChild(msgt);
    
    _messageListView->pushBackCustomItem(lo);
    _messageListView->refreshView();
    _messageListView->scrollToBottom(0.3, true);
}

void LHGameChatView::setTitle(const std::string &title){
    _titleView->setString(title);
}