//------.cpp
#include "PlayScene.h"
#include <iostream>
#include "LHMacro.h"
#include "ThirdPartyHelper.h"
USING_NS_CC;
Scene* PlayScene::createScene(cocos2d::CCDictionary *dic)
{
	auto scene = Scene::create();
    scene->setTag(624);
	auto layer = PlayScene::create();
	layer->initDict(dic);
	scene->addChild(layer);
	return scene;
}

bool PlayScene::initDict(cocos2d::CCDictionary *dic)
{
    remlan = (RemLan*)dic->objectForKey("lan");
    
    Size vs = Director::getInstance()->getVisibleSize();
    
    cocos2d::ui::Button *bt = cocos2d::ui::Button::create("play.png");
    bt->addTouchEventListener([](Ref* ps,cocos2d::ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
             Director::getInstance()->popScene();
        }
    });
    bt->setPosition(Vec2(40, 40));
    this->addChild(bt,1);
    
    //score
    ui::Text *score = ui::Text::create(StringUtils::format("%ld",_scorevalue), Common_Font, 40);
    score->setPosition(Vec2(vs.width/2, vs.height - score->getContentSize().height/2));
    this->addChild(score);
    _score = score;
    
    //time
    ui::Text *time = ui::Text::create(StringUtils::format("%lf",_timeuse), Common_Font, 35);
    time->setPosition(Vec2(vs.width - time->getContentSize().width/2, vs.height - time->getContentSize().height/2 - 5));
    this->addChild(time);
    _time = time;
    
    //show answer
    auto sa = ui::Button::create();
    sa->ignoreContentAdaptWithSize(false);
    sa->setSize(Size(60,60));
    sa->setTitleFontSize(40);
    sa->setTitleText("A");
    sa->setPosition(Vec2(vs.width - 40, vs.height - 80));
    sa->addTouchEventListener(CC_CALLBACK_2(PlayScene::showAn, this));
    this->addChild(sa,1);
    
    this->genWord();
    
	return true;
}

void PlayScene::showAn(Ref*,ui::Widget::TouchEventType type){
    if (type == ui::Widget::TouchEventType::ENDED){
        std::string tmp;
        StringUtils::UTF16ToUTF8(currentanswer, tmp);
        
        Size vs = Director::getInstance()->getVisibleSize();
        
        auto layout = ui::Layout::create();
        layout->setSize(vs);
        layout->addTouchEventListener([layout,this](Ref*,ui::Widget::TouchEventType type){
            if (type == ui::Widget::TouchEventType::ENDED) {
                layout->removeFromParent();
                ThirdPartyHelper::setAd(SET_AD_HID);
                this->genWord();
            }
        });
        this->addChild(layout,2);
        
        Color4B b = Color4B::BLACK;
        b.a = 120;
        auto lc = LayerColor::create(b, vs.width, vs.height);
        layout->addChild(lc);
        
        auto an = ui::Text::create(tmp, Common_Font, 45);
        an->setPosition(Vec2(vs.width/2, vs.height/2));
        layout->addChild(an);
        
        an = ui::Text::create(currentWord->getSound()->getCString(), Common_Font, 35);
        an->setPosition(Vec2(vs.width/2, vs.height/2 - an->getContentSize().height-5));
        layout->addChild(an);
        
        ThirdPartyHelper::setAd(SET_AD_SHOW);
    }
}

void PlayScene::update(float delta){
    if (_timeuse>=0) {
        _timeuse += delta;
        _time->setString(StringUtils::format("%lf",_timeuse));
    }
}

void PlayScene::onEnterTransitionDidFinish(){
    scheduleUpdate();
}

void PlayScene::onExitTransitionDidStart(){
    unscheduleUpdate();
}

void PlayScene::genWord(){
    
    if (currentlayout) {
        currentlayout->removeFromParent();
    }

    int index = CCRANDOM_0_1() * remlan->words.size();
    RemWord *w = remlan->words.at(index);
    
    auto learn = w->getLearn();
    std::string learnStr(learn->getCString());
    std::u16string u16l;
    StringUtils::UTF8ToUTF16(learnStr, u16l);
    std::vector<char16_t> chs = StringUtils::getChar16VectorFromUTF16String(u16l);

    std::string al(remlan->getAl()->getCString());
    std::u16string alu16s;
    StringUtils::UTF8ToUTF16(al, alu16s);

    Size vs = Director::getInstance()->getVisibleSize();
    int lineCount = 6;
    int columnCount = 6;
    float bw = vs.width/lineCount;
    float bh = vs.height/2/columnCount;

    int leftcount = lineCount*columnCount - chs.size();
    while(leftcount>0){
        int in = CCRANDOM_0_1() * alu16s.size();
        char16_t tmp = alu16s[in];
        int insert = CCRANDOM_0_1() * chs.size();
        chs.insert(chs.begin() + insert, tmp);
        leftcount -- ;
    }
    
    //gen ui
    auto layout = ui::Layout::create();
    layout->setPosition(Vec2(0, 0));
    layout->setSize(vs);
    this->addChild(layout, 0);
    for (int i =0 ; i<lineCount*columnCount; i++) {
        
        int line = i/columnCount;
        int col = i%columnCount;
        
        auto tbt = ui::Button::create("play.png");
        tbt->setSize(Size(bw, 40));
        tbt->setTitleFontSize(40);
        tbt->setScale9Enabled(true);
        char16_t tmp16c = chs.at(i);
        std::u16string tmp16;
        tmp16.push_back(tmp16c);
        std::string tmp8;
        StringUtils::UTF16ToUTF8(tmp16, tmp8);
        tbt->setTag(6240);
        tbt->setTitleText(tmp8);
        tbt->setPosition(Vec2(bw/2+line*bw, vs.height/2 - col*bh));
        tbt->setTitleColor(Color3B::RED);
        tbt->addTouchEventListener([this](Ref* charbt,ui::Widget::TouchEventType type){
            
            if (type == ui::Widget::TouchEventType::ENDED) {
                int comp = this->checkComplete(charbt);
                if (comp==0) {
                    this->scoreAndMoveOn();
                }else if(comp==1){
                    this->wrongAn();
                }
            }
        });
        layout->addChild(tbt);
    }
    
    std::string editstring;
    for (int i=0; i<u16l.size(); i++) {
        editstring.append("_");
    }
    auto edit = ui::Button::create("play.png");
    edit->setTag(0);
    edit->setTitleFontSize(35);
    edit->setScale9Enabled(true);
    edit->setSize(Size(vs.width/3*2,vs.height/6));
    edit->setTitleText(editstring);
    edit->setPosition(Vec2(vs.width/2, vs.height/4*3));
    edit->addTouchEventListener([this](Ref* charbt,ui::Widget::TouchEventType type){
        if(currentedit.size()==0){
            return;
        }
        
        ui::Button *cbt = (ui::Button*)charbt;
        if (type == ui::Widget::TouchEventType::ENDED) {
            //remove one
            currentedit.pop_back();
            std::string tmpedit;
            StringUtils::UTF16ToUTF8(currentedit, tmpedit);
            int leftcount = currentanswer.length() - currentedit.length();
            while (leftcount>0) {
                tmpedit.append("_");
                leftcount--;
            }
            cbt->setTitleText(tmpedit);
            
            if (cbt->getTag()==1) {
                this->enableAllCharBt(true);
                cbt->setTag(0);
            }
        }
    });
    editbutton = edit;
    layout->addChild(edit);
    
    currentlayout = layout;
    currentanswer = u16l;
    currentWord = w;
}

int PlayScene::checkComplete(cocos2d::Ref *charbt){
    ui::Button *cbt = (ui::Button*)charbt;
    std::string clickchar = cbt->getTitleText();
    std::u16string tmpu16;
    StringUtils::UTF8ToUTF16(clickchar, tmpu16);
    
    currentedit.append(tmpu16);
    
    int leftcount = currentanswer.length() - currentedit.length();
    std::string tmpedit;
    StringUtils::UTF16ToUTF8(currentedit, tmpedit);
    while (leftcount>0) {
        tmpedit.append("_");
        leftcount--;
    }
    editbutton->setTitleText(tmpedit);
    
    if (currentanswer.compare(currentedit)==0) {
        return 0;
    }else{
        if (currentanswer.length() == currentedit.length()) {
            return 1;
        }else{
            return 2;
        }
    }
}

void PlayScene::enableAllCharBt(bool enable){
    Vector<Node*> children = currentlayout->getChildren();
    for (int i =0 ; i<children.size(); i++) {
        Node *child = children.at(i);
        if(child->getTag()==6240){
            ui::Button *cbt = (ui::Button*)child;
            cbt->setEnabled(enable);
        }
    }
}

void PlayScene::scoreAndMoveOn(){
    //socre
    int score = 1;
    
    _scorevalue += score;
    _score->setString(StringUtils::format("%ld",_scorevalue));
    
    _timeuse = -1;
    this->genWord();
}

void PlayScene::wrongAn(){
    enableAllCharBt(false);
    editbutton->setTag(1);
}