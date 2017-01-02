//
//  MessageController.cpp
//  SnakeServer
//
//  Created by 查启杰 on 16/10/16.
//  Copyright © 2016年 查 启杰. All rights reserved.
//

#include "MessageController.hpp"
#include <sys/socket.h>
#include "GameNetLogic.hpp"
#include "BitTool.hpp"


MessageController* MessageController::_instance = nullptr;
int MessageController::m_serverSocket = 0;
MessageController::MessageController()
{
    
}

MessageController::~MessageController()
{
    if(_instance != nullptr)
    {
        delete _instance;
    }
}

void MessageController::init(int server)
{
    m_serverSocket = server;
}

MessageController* MessageController::Instance()
{
    if(_instance == nullptr)
    {
        _instance = new MessageController();
    }
    return _instance;
}

void MessageController::addRecv(MESSAGE_DATA data)
{
    //m_recvQueue.push(data);
    recv(data);
}

void MessageController::addSend(MESSAGE_DATA data)
{
    //m_sendQueue.push(data);
}

void MessageController::sendMessage(google::protobuf::Message *msg, int msgID, int sock)
{
    int len = (int)(msg->ByteSizeLong());
    BYTE* buff = new BYTE[len];
    msg->SerializeToArray(buff, len);
    
    BYTE* data = new BYTE[len + 8];
    BitTool::writeInt(data, 0, len);
    BitTool::writeInt(data,4,msgID);
    BitTool::writeBytes(data, buff, 8, len);
    
    MESSAGE_DATA md;
    md.msgLen = len + 8;
    md.msgID = msgID;
    md.socket = sock;
    md.msgData = data;
    send(md);
    delete[] buff;
    delete[] data;
}


void MessageController::send(MESSAGE_DATA data)
{
    ::send(data.socket, data.msgData, data.msgLen, 0);
}

void MessageController::recv(MESSAGE_DATA data)
{
    //这段 代码可以通过脚本生成. 放在另外一个文件里,另外一个文件由脚本生成.
    switch (data.msgID) {
        case PROTOCOL::__LoginReq :
            OnLoginReq(data.msgData, data.msgLen, data.socket);
            break;
        default:
            break;
    }
}

void MessageController::update()
{
    
}



//以下这些代码可以通过脚本生成一部分.
void MessageController::OnLoginReq(BYTE buff[], int size, int sock)
{
    LoginReq* req = new LoginReq();
    req->ParseFromArray(buff, size);
    GameNetLogic::getInstance()->OnLoginReq(req, sock);
    printf("on login now user name %s, protoid %d\n\n",req->name().c_str(), req->proid());
}
