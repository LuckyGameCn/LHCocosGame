//
//  LHPomeloManager.h
//  LHCocosFirstGame
//
//  Created by huji on 14-12-19.
//
//

#ifndef __LHCocosFirstGame__LHPomeloManager__
#define __LHCocosFirstGame__LHPomeloManager__

#include "cocos2d.h"
#include <pomelo.h>

#define Pomelo_Host "127.0.0.1"
#define Pomelo_Port 3014

//#define Pomelo_Host "114.113.202.141"
//#define Pomelo_Port 3088

class LHPomeloManager{
public:
//    static LHPomeloManager* getInstance();
    LHPomeloManager();
    virtual ~LHPomeloManager();
    
    const std::string& getUserName(){
        return _username;
    }
    const std::string& getChannel(){
        return _channel;
    }
    
    bool connect(const std::string& username,const std::string& channel);
    
    std::function<void(int status, json_t *resp)> onEnterChannel;
    std::function<void(json_t *resp)> onMessage;
    
    pc_client_t *pomeloClient;
private:
    std::string _username;
    std::string _channel;
};

#endif /* defined(__LHCocosFirstGame__LHPomeloManager__) */
