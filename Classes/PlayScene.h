#include "cocos2d.h"

NS_CC_BEGIN

#define TRCOUNT 10

class PlayScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int level);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual ~PlayScene();
    
    void initWithLevel(int level);
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, bool transformUpdated);
    void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
    
private:
    int plevel;
};

// __HELLOWORLD_SCENE_H__

NS_CC_END
