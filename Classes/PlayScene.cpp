//------.cpp
#include "PlayScene.h"
#include "UIText.h"
#include "UIButton.h"
#include "UILayout.h"
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
    
    cocos2d::ui::Button *bt = cocos2d::ui::Button::create("play.png");
    bt->addTouchEventListener([](Ref* ps,cocos2d::ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
             Director::getInstance()->popScene();
        }
    });
    bt->setPosition(Vec2(40, 40));
    this->addChild(bt,1);
    
    this->genWord();
    
	return true;
}

void PlayScene::genWord(){
    
//    cocos2d::Vector<CCString*> chs;
    std::vector<std::u16string> chs;
    
    int index = CCRANDOM_0_1() * remlan->words.size();
    RemWord *w = remlan->words.at(4);
    auto learn = w->getLearn();
    std::string learnStr(learn->getCString());
    std::u16string u16l;
    StringUtils::UTF8ToUTF16(learnStr, u16l);
    for (int i =0 ; i<u16l.length(); i++) {
        std::u16string tmp = &u16l.at(i);
//        const unsigned char *s = (const unsigned char*)tmp.c_str();
//        int len = tmp.length();
        chs.push_back(tmp);
//        chs.pushBack(CCString::createWithData(s, len));
    }
    
    //gen ui
    Size vs = Director::getInstance()->getVisibleSize();
    auto layout = ui::Layout::create();
    layout->setPosition(Vec2(0, 0));
    layout->setSize(vs);
    this->addChild(layout, 0);
    
    for (int i =0 ; i<chs.size(); i++) {
        auto tbt = ui::Button::create("play.png");
        float bw = vs.width/5;
        tbt->setSize(Size(bw, 40));
        tbt->setTitleFontSize(40);
        std::u16string tmp16 = chs.at(i);
        std::string tmp8;
        StringUtils::UTF16ToUTF8(tmp16, tmp8);
        tbt->setTitleText(tmp8);
        tbt->setPosition(Vec2(bw/2+i*bw, 200));
        tbt->setTitleColor(Color3B::RED);
        layout->addChild(tbt);
    }
}