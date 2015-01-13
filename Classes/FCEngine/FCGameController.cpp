//
//  FCGameController.cpp
//  LHCocosFirstGame
//
//  Created by user on 15-1-4.
//
//

#include "FCGameController.h"
#include "Dispatcher.h"

static FCGameController *_instance =  nullptr;

FCGameController* FCGameController::getInstance(){
    if (_instance == nullptr) {
        _instance = new FCGameController();
    }
    return _instance;
}

void FCGameController::connect(){
    if (!_pomeloManager) {
        _pomeloManager = new LHPomeloManager();
        _pomeloManager->connect("2dxhuji", "fcgame");
        _pomeloManager->onMessage = [](json_t *resp){
            
        };
        this->registerDispatch();
        this->nextAction();
    }
}

void FCGameController::disConnect(){
    if (_pomeloManager) {
        _pomeloManager->disconnect();
        delete _pomeloManager;
    }
}

void FCGameController::registerDispatch(){
    if (_pomeloManager) {
        Dispatcher::executeMain([this](){
            if (_waitingActions.size()>0 && _nextAction) {
                if (this->onActionGet) {
                    FCAction *ac = _waitingActions.front();
                    ac->retain();
                    ac->autorelease();
                    _waitingActions.erase(0);
                    _nextAction = false;
                    onActionGet(ac);
                }
            }
            
            this->registerDispatch();
        });
    }
}

void FCGameController::nextAction(){
    _nextAction = true;
}

void FCGameController::sendAction(FCAction *action){
    
}