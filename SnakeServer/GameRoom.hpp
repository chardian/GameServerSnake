//
//  GameRoom.hpp
//  SnakeServer
//
//  Created by 查启杰 on 17/1/1.
//  Copyright © 2017年 查 启杰. All rights reserved.
//

#ifndef GameRoom_hpp
#define GameRoom_hpp
#include "qi.pb.h"
#include <stdio.h>
#include "GlobalHeader.h"
#include <vector>
using namespace std;

class GameUser
{
public:
    GameUser(int userid, int _state = UserState::STATE_NOT_READY){
        m_userID = userid;
        m_state = _state;
    }
    int m_userID;
    int m_state;
    inline void reset()
    {
        m_state = UserState::STATE_NOT_READY;
    }
};

class GameRoom
{
public:
    int m_roomID;
    int m_count;
    int m_max;
    char* roomName;
    GameRoom();
    ~GameRoom();
    void ToEntity(Room*);
    vector<GameUser> m_users;
    
};
#endif /* GameRoom_hpp */
