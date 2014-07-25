//------.cpp
#include "PlayScene.h"
#include "UIButton.h"
#include "UILayout.h"
#include <iostream>
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
    ui::Text *score = ui::Text::create(StringUtils::format("%lf",126.021f), nullptr, 40);
    score->setPosition(Vec2(vs.width/2, vs.height - score->getContentSize().height/2));
    this->addChild(score);
    _score = score;
    
    this->genWord();
    
	return true;
}

void PlayScene::genWord(){
    
//    std::u16string allchar;
    
    
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
//        chs.insert(chs.begin() + insert, tmp);
        chs.push_back(tmp);
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
        std::u16string tmp16(&tmp16c);
        std::string tmp8;
        StringUtils::UTF16ToUTF8(tmp16, tmp8);
        printf("u8 %s %ld u16 %ld\n",tmp8.c_str(),tmp8.length(),tmp16.length());
        tbt->setTitleText(tmp8);
        tbt->setPosition(Vec2(bw/2+line*bw, vs.height/2 - col*bh));
        tbt->setTitleColor(Color3B::RED);
        layout->addChild(tbt);
    }
    
}