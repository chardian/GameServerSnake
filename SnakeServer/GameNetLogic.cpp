//
//  GameNetLogic.cpp
//  SnakeServer
//
//  Created by 查启杰 on 17/1/1.
//  Copyright © 2017年 查 启杰. All rights reserved.
//

#include "GameNetLogic.hpp"

#include "MessageController.hpp"
#include "ClientData.h"
#include "GameLobby.hpp"
#include "BitTool.hpp"

GameNetLogic* GameNetLogic::_instance = nullptr;

GameNetLogic::GameNetLogic()
{
    _sendBuff = new boost::circular_buffer<BYTE>(BUFF_LEN);
}

GameNetLogic::~GameNetLogic()
{
    delete _sendBuff;
}

GameNetLogic* GameNetLogic::getInstance()
{
    if(_instance == nullptr)
    {
        _instance = new GameNetLogic();
    }
    return _instance;
}

void GameNetLogic::OnLoginReq(LoginReq *req, int sock)
{
    GameLobby* lobby = GameLobby::getInstance();
    lobby->getAvaibleRoom();
    //返回登录成功
    LoginAck ack;
    ack.set_id(getNewUserID());
    ack.set_ret(Result::Success);
    MessageController::Instance()->sendMessage(&ack, ack.proid(), sock);
    //告诉玩家房间信息
    OnGetRoomReq(nullptr, sock);
}



void GameNetLogic::OnEnterRoomReq(EnterRoomReq *req, int sock){
    //判断房间是否人满了
   GameRoom* gr = GameLobby::getInstance()->getRoomByID(req->roomid());
    if(gr == nullptr)
    {
        //nonono
    }else
    {
        if(gr->m_users.size() >= 2)
        {
            //人满了,需要添加人满了的错误提示
        }else
        {
            EnterRoomAck ack;
            ack.set_ret(Result::Success);
            
            ClientData* cli = ClientData::GetClientDataBySocket(sock);
            GameUser gu(cli->m_userID);
            gr->m_users.push_back(gu);
            for(vector<GameUser>::iterator it = gr->m_users.begin(); it != gr->m_users.end();it++)
            {
                    RoomUser *user = ack.add_users();
                    
            }
            
            
        }
    }
}

void GameNetLogic::OnChessReq(ChessReq  *req, int sock){
    
}

void GameNetLogic::OnGetRoomReq(GetRoomReq  *req, int sock){
    if(req != nullptr)
    {
            //有数据
    }
    GetRoomAck ack;
    ack.set_ret(Result::Success);
    vector<GameRoom> *vec = GameLobby::getInstance()->getAllRoom();
    for (vector<GameRoom>::iterator it = vec->begin(); it != vec->end(); it++) {
        Room* r = ack.add_rooms();
        it->ToEntity(r);
    }
    MessageController::Instance()->sendMessage(&ack, ack.proid(), sock);
}

