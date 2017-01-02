//
//  Client.h
//  SnakeServer
//
//  Created by 查启杰 on 16/10/16.
//  Copyright © 2016年 查 启杰. All rights reserved.
//

#ifndef ClientData_h
#define ClientData_h

#include "qi.pb.h"
#include "GlobalHeader.h"
#include <boost/circular_buffer.hpp>
#include <vector>
using namespace boost;
class ClientData
{
public:
    ClientData(int socket);
    ~ClientData();
    void display();
    int m_socket;//socket id
    int m_userID;//user id //database's id
    int m_snakeID;// logic id
    bool write(BYTE [], int len);
    bool submitRead(BYTE*, const int len);
    bool read(BYTE*, int len);
    inline int getBufferLen(){
        return (int)_buff->size();
    }
    static ClientData* GetClientDataBySocket(int);
    static ClientData* GetClientDataByUserID(int);
private:
    static int _ID;
    circular_buffer<BYTE>* _buff;
    //所有的ClientData
    static std::vector<ClientData*> *m_list;
};

#endif /* ClientData_h */
