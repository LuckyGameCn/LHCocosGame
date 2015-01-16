//
//  FCMoveObject.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-11-28.
//
//

#include "FCMoveObject.h"
#include "FCGameConfig.h"
#include "FCGameLayer.h"
USING_NS_CC;
bool FCMoveObject::move(int tx, int ty){
    return _gameLayer->move(this, tx, ty);
}

void FCMoveObject::changePosition(int tx, int ty){
    if (onMoveWillMove) onMoveWillMove(this,tx,ty);
    int fromx = tx;
    int fromy = ty;
    FCObject::changePosition(tx, ty);
    if (onMoveDidMove) onMoveDidMove(this,fromx,fromy);
}

bool FCMoveObject::stopMove(const std::function<void()>& stopComplete){
    auto mvac = aSprite->getActionByTag(FCMOVEACTIONTAG);
    if (!mvac||mvac->isDone()) {
        if (stopComplete) {
            stopComplete();
        }
    }else{
        aSprite->stopAllActions();
        Vec2 from = _gameLayer->tileToPosition(tx, ty);
        Vec2 cu = aSprite->getPosition();
        int tox = tx;
        int toy = ty;
        if (cu.x>from.x) {
            tox = tx+1;
        }else if (cu.x<from.x){
            tox = tx-1;
        }else if (cu.y>from.y){
            toy = toy+1;
        }else if (cu.y<from.y){
            toy = toy-1;
        }
        Vec2 to = _gameLayer->tileToPosition(tox, toy);
        float len = to.distance(cu);
        auto mvto = MoveTo::create(len/moveSpeed, to);
        auto call = CallFunc::create([stopComplete,this,tox,toy](){
            _gameLayer->changePosition(this, tox, toy);
            if (stopComplete) stopComplete();
        });
        auto sq = Sequence::create(mvto,call,NULL);
        aSprite->runAction(sq);
    }
    return true;
}