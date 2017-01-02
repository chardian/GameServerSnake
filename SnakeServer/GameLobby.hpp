//
//  GameLobby.hpp
//  SnakeServer
//
//  Created by 查启杰 on 17/1/1.
//  Copyright © 2017年 查 启杰. All rights reserved.
//

#ifndef GameLobby_hpp
#define GameLobby_hpp
#include <vector>
#include <stdio.h>
#include "GameRoom.hpp"
using namespace std;
class GameLobby
{
private:
    vector<GameRoom>* m_rooms;
    static GameLobby* _instance;
public:
    vector<GameRoom>* getAllRoom();
    vector<GameRoom>* getAvaibleRoom();
    static GameLobby* getInstance();
    GameRoom* getRoomByID(int id);
    GameLobby();
    ~GameLobby();
};
#endif /* GameLobby_hpp */
