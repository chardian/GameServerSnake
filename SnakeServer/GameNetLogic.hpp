//
//  GameNetLogic.hpp
//  SnakeServer
//
//  Created by 查启杰 on 17/1/1.
//  Copyright © 2017年 查 启杰. All rights reserved.
//

#ifndef GameNetLogic_hpp
#define GameNetLogic_hpp
#include <map>
#include <stdio.h>
#include "qi.pb.h"
#include "GlobalHeader.h"
#include "GameLobby.hpp"
#include <boost/circular_buffer.hpp>

using namespace std;

//typedef void (*callBack)(BYTE[],int);

class GameNetLogic
{
private:
    static GameNetLogic* _instance;
    boost::circular_buffer<BYTE> *_sendBuff;
    //当前ID分配到了某个值
    int userID = 100;
    inline int getNewUserID()
    {
        int a = userID;
        userID++;
        return a;
    }
    GameNetLogic();
    ~GameNetLogic();
public:
    static GameNetLogic* getInstance();
    //std::map<int,callBack> m_map;
    void OnLoginReq(LoginReq*, int sock );
    void OnEnterRoomReq(EnterRoomReq* , int sock);
    void OnChessReq(ChessReq* ,int sock);
    void OnGetRoomReq(GetRoomReq* ,int sock);
};
#endif /* GameNetLogic_hpp */
