
#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int level);

    GameOverScene();
    virtual ~GameOverScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void initWithLevel(int level);
    
    void again(cocos2d::Ref* pSender);
    void back(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
    
private:
    int rlevel;
};

//#endif // __HELLOWORLD_SCENE_H__
