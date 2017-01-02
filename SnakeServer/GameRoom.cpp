//
//  GameRoom.cpp
//  SnakeServer
//
//  Created by 查启杰 on 17/1/1.
//  Copyright © 2017年 查 启杰. All rights reserved.
//

#include "GameRoom.hpp"

GameRoom::GameRoom()
{
    roomName = nullptr;
    this->m_count = 0;
    this->m_max = 2;
    this->m_roomID = -1;
}



GameRoom::~GameRoom()
{
    if(roomName != nullptr)
    {
        delete[] roomName;
    }
}

void GameRoom::ToEntity(Room* r)
{
    r->set_roomid(this->m_roomID);
    r->set_max(this->m_max);
    r->set_count(this->m_count);
    r->set_roomname(this->roomName);
}

