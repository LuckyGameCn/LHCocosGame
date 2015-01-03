//
//  FCAlgo.cpp
//  LHCocosFirstGame
//
//  Created by huji on 14-11-29.
//
//

#include "FCAlgo.h"
USING_NS_CC;

static Vector<FCVec2*> getNeibors(std::vector<std::vector<int>>& graph,FCVec2* vc){
    Vector<FCVec2*> neibors;
    for (int i=0; i<4; i++) {
        int v = -1;
        int nx;
        int ny;
        if (i==0&&(vc->y+1)<graph.size()) {
            //up
            nx = vc->x;
            ny = vc->y+1;
            v = graph[ny][nx];
        }else if (i==1&&(vc->y-1)>=0){
            //down
            nx = vc->x;
            ny = vc->y-1;
            v = graph[ny][nx];
        }else if (i==2&&(vc->x-1)>=0){
            //left
            nx = vc->x-1;
            ny = vc->y;
            v = graph[ny][nx];
        }else{
            if (vc->x+1<graph[0].size()) {
                //right
                nx = vc->x+1;
                ny = vc->y;
                v = graph[ny][nx];
            }
        }
        if (v>=0) {
            neibors.pushBack(FCVec2::create(nx,ny));
        }
    }
    return neibors;
}

inline int heuristic(int nextx,int nexty,cocos2d::Vec2& end){
    return abs(nextx - end.x) + abs(nexty - end.y);
}

std::vector<cocos2d::Vec2>* FCAlgo::A_Star(std::vector<std::vector<int>>& graph,cocos2d::Vec2 start,cocos2d::Vec2 end){
    std::vector<cocos2d::Vec2>* path = new std::vector<cocos2d::Vec2>();
    PriorityQueue<Vec2> fronter;
    Map<std::string, FCVec2*> cameFrom;
    Map<std::string, CCInteger*> costSoFar;
    fronter.put(start, 0);
    FCVec2* fcst = FCVec2::create(start);
    cameFrom.insert(fcst->toString(), fcst);
    costSoFar.insert(fcst->toString(), CCInteger::create(0));
    while (!fronter.empty()) {
        Vec2 cu = fronter.get();
        if (cu.equals(end)) {
            break;
        }
        FCVec2 *fccu = FCVec2::create(cu);
        Vector<FCVec2*> neibors = getNeibors(graph,fccu);
        int csf = costSoFar.at(fccu->toString())->getValue();
        for (auto next : neibors) {
            int new_cost = csf + 1;
            std::string nextkey = next->toString();
            if (costSoFar.find(nextkey)==costSoFar.end() || new_cost<costSoFar.at(nextkey)->getValue()) {
                costSoFar.insert(nextkey, CCInteger::create(new_cost));
                int prio = new_cost + heuristic(next->x,next->y,end);
                fronter.put(Vec2(next->x, next->y), prio);
                cameFrom.insert(nextkey, fccu);
            }
        }
    }
    FCVec2 *fc = FCVec2::create(end);
    while (cameFrom.find(fc->toString())!=cameFrom.end()) {
        path->insert(path->begin(), Vec2(fc->x, fc->y));
        fc = cameFrom.at(fc->toString());
        Vec2 fcv(fc->x,fc->y);
        if (fcv.equals(start)) {
            break;
        }
    }
    return path;
}