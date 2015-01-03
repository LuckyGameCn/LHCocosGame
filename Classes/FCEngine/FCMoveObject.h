//
//  FCMoveObject.h
//  LHCocosFirstGame
//
//  Created by huji on 14-11-28.
//
//

#ifndef __LHCocosFirstGame__FCMoveObject__
#define __LHCocosFirstGame__FCMoveObject__

#include "FCObject.h"

#define FCMOVEACTIONTAG 3

class FCMoveObject : public FCObject{
public:
    bool move(int tx,int ty);
    bool stopMove(const std::function<void()>& stopComplete);
    virtual void changePosition(int tx,int ty);
    
    //member
    std::function<void()> onMoveBegin;
    std::function<void(FCMoveObject* me,int totx,int toty)> onMoveWillMove;
    std::function<void(FCMoveObject* me,int fromtx,int fromty)> onMoveDidMove;
    std::function<void()> onMoveEnd;
    int moveLen = 0;
    bool pathFindVisible = false;
    float moveSpeed = 300;
};

#endif /* defined(__LHCocosFirstGame__FCMoveObject__) */
