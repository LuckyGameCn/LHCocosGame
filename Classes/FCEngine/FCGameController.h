//
//  FCGameController.h
//  LHCocosFirstGame
//
//  Created by user on 15-1-4.
//
//

#ifndef __LHCocosFirstGame__FCGameController__
#define __LHCocosFirstGame__FCGameController__

#include <stdio.h>
#include "cocos2d.h"
#include "FCAction.h"
#include "LHPomeloManager.h"

class FCGameController{
public:
    static FCGameController* getInstance();
    
    //long link
    void connect();
    void disConnect();
    
    std::function<void(FCAction *action)> onActionGet;
    void sendAction(FCAction *action);
    void nextAction();
private:
    void registerDispatch();
    
    cocos2d::Vector<FCAction*> _waitingActions;
    bool _nextAction;
    
    LHPomeloManager *_pomeloManager;
};

#endif /* defined(__LHCocosFirstGame__FCGameController__) */
