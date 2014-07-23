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
    
    std::u16string allchar;
    
    int index = CCRANDOM_0_1() * remlan->words.size();
    RemWord *w = remlan->words.at(index);
    
    auto learn = w->getLearn();
    std::string learnStr(learn->getCString());
    std::u16string u16l;
    StringUtils::UTF8ToUTF16(learnStr, u16l);
    for (int i =0 ; i<u16l.length(); i++) {
        char16_t tmp = u16l.at(i);
        allchar.append(&tmp);
    }
    
    std::string al(remlan->getAl()->getCString());
    std::u16string alu16s;
    StringUtils::UTF8ToUTF16(al, alu16s);
    
    Size vs = Director::getInstance()->getVisibleSize();
    int lineCount = 6;
    int columnCount = 6;
    float bw = vs.width/lineCount;
    float bh = vs.height/2/columnCount;
    
    int leftcount = lineCount*columnCount - allchar.size();
    while(leftcount>0){
        int in = CCRANDOM_0_1() * alu16s.size();
        char16_t tmp = alu16s.at(in);
        int insert = CCRANDOM_0_1() * allchar.size();
        allchar.insert(insert, &tmp);
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
        char16_t tmp16c = allchar.at(i);
        std::u16string tmp16(&tmp16c);
        std::string tmp8;
        StringUtils::UTF16ToUTF8(tmp16, tmp8);
        tbt->setTitleText(tmp8);
        tbt->setPosition(Vec2(bw/2+line*bw, vs.height/2 - col*bh));
        tbt->setTitleColor(Color3B::RED);
        layout->addChild(tbt);
    }
}