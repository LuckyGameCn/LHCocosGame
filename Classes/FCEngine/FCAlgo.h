//
//  FCAlgo.h
//  LHCocosFirstGame
//
//  Created by huji on 14-11-29.
//
//

#ifndef __LHCocosFirstGame__FCAlgo__
#define __LHCocosFirstGame__FCAlgo__

#include "cocos2d.h"
#include <queue>

#define MAXTILEMAP_WIDTH 200
#define MAXTILEMAP_HEIGHT 200

template<typename T, typename Number=int>
struct PriorityQueue {
    typedef std::pair<Number, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
    std::greater<PQElement>> elements;
    
    inline bool empty() { return elements.empty(); }
    
    inline void put(T item, Number priority) {
        elements.emplace(priority, item);
    }
    
    inline T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

class FCVec2 : public cocos2d::Ref{
public:
    static FCVec2* create(cocos2d::Vec2& po){
        auto fcv2 = FCVec2::create(po.x,po.y);
        return fcv2;
    };
    static FCVec2* create(int x,int y){
        auto fcv2 = FCVec2::create();
        fcv2->x=x;
        fcv2->y=y;
        return fcv2;
    };
    bool init(){return true;};
    CREATE_FUNC(FCVec2);
    
    std::string toString(){
        return cocos2d::StringUtils::format("%d,%d",x,y);
    };
    
    int x;
    int y;
};

class FCAlgo{
public:
    //-1 means block.
    static std::vector<cocos2d::Vec2>* A_Star(std::vector<std::vector<int>>& graph,cocos2d::Vec2 start,cocos2d::Vec2 end);
};

#endif /* defined(__LHCocosFirstGame__FCAlgo__) */
