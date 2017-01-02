//
//  GameLobby.cpp
//  SnakeServer
//
//  Created by 查启杰 on 17/1/1.
//  Copyright © 2017年 查 启杰. All rights reserved.
//

#include "GameLobby.hpp"


GameLobby* GameLobby::_instance = nullptr;
GameLobby* GameLobby::getInstance()
{
    if(_instance == nullptr)
    {
        _instance = new GameLobby();
    }
    return _instance;
}

GameLobby::GameLobby()
{
    m_rooms = new vector<GameRoom>(MAX_ROOM);
    vector<GameRoom>::iterator it;
    int i =0;
    for (it = m_rooms->begin(); it != m_rooms->end(); it++,i++) {
        it->m_max = 2;
        it->m_count = 0;
        it->roomName = new char[16];
        it->m_roomID = i;
        strcpy(it->roomName,"Room");
        char c = i;
        strcat(it->roomName, &c);
    }
}

GameLobby::~GameLobby()
{
    if(m_rooms != nullptr)
    {
        delete m_rooms;
    }
    
}

vector<GameRoom>* GameLobby::getAllRoom()
{
    return m_rooms;
}

vector<GameRoom>* GameLobby::getAvaibleRoom()
{
    return m_rooms;
}
