//
//  FCGameController.cpp
//  LHCocosFirstGame
//
//  Created by user on 15-1-4.
//
//

#include "FCGameController.h"
#include "Dispatcher.h"

//actions
#include "FCCreateUnitAction.h"
#include "FCControlAction.h"
#include "FCShowUIAction.h"
#include "FCMoveAction.h"
#include "FCAttackAction.h"

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
        _pomeloManager->onEnterChannel = [this](int status, json_t *resp){
            this->registerDispatch();
            this->nextAction();
        };
        _pomeloManager->onMessage = [this](json_t *resp){
             json_t *msg = json_object_get(resp, "msg");
            const char *msgvalue = json_string_value(msg);
            char *p = strstr(msgvalue, "#");
            if (p) {
                char type[10];
                memcpy(type, msgvalue, p-msgvalue);
                type[p-msgvalue]='\0';
                FCAction *ac = nullptr;
                if (strcmp(type, "cr")==0) {
                    ac = new FCCreateUnitAction();
                }else if(strcmp(type, "co")==0){
                    ac = new FCControlAction();
                }else if(strcmp(type, "su")==0){
                    ac = new FCShowUIAction();
                }else if(strcmp(type, "mv")==0){
                    ac = new FCMoveAction();
                }else if(strcmp(type, "at")==0){
                    ac = new FCAttackAction();
                }
                if (ac) {
                    ac->autorelease();
                    ac->initFrom(msg);
                    _waitingActions.pushBack(ac);
                }
            }
        };
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