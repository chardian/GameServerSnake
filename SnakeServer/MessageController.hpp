//
//  MessageController.hpp
//  SnakeServer
//
//  Created by 查启杰 on 16/10/16.
//  Copyright © 2016年 查 启杰. All rights reserved.
//

#ifndef MessageController_hpp
#define MessageController_hpp

#include <stdio.h>
#include "qi.pb.h"
#include <string>
#include <boost/circular_buffer.hpp>
#include "GlobalHeader.h"
#include <queue>
#include <google/protobuf/message.h>

using namespace std;

class MessageController
{
    
public:
    MessageController();
    ~MessageController();
    static void init(int serverSocket);
    static MessageController* Instance();
    void addSend(MESSAGE_DATA);
    void addRecv(MESSAGE_DATA);
    void recv(MESSAGE_DATA);
    void sendMessage(google::protobuf::Message *, int msgID, int sock);
    //void sendMessage(BYTE* data, int sock, int id, int len);
    void send(MESSAGE_DATA);
    
    void OnLoginReq(BYTE buff[], int size, int sock);
private:
    static int m_serverSocket;
    
void OnLogout(int userID)
{
    
}
    
    
private:
    static MessageController* _instance;
    queue<MESSAGE_DATA> m_recvQueue;
    queue<MESSAGE_DATA> m_sendQueue;
    void update();
};


#endif /* MessageController_hpp */
