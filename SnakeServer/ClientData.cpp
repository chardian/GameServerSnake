//
//  Client.cpp
//  SnakeServer
//
//  Created by 查启杰 on 16/10/16.
//  Copyright © 2016年 查 启杰. All rights reserved.
//

#include <stdio.h>
#include "ClientData.h"
int ClientData::_ID=0;
std::vector<ClientData*>* ClientData::m_list = nullptr;

ClientData::ClientData(int socket)
{
    m_socket = socket;
    m_userID = _ID;
    m_snakeID = m_userID;
    _ID++;
    _buff = new circular_buffer<BYTE>(BUFF_LEN);
    if(m_list == nullptr)
    {
        m_list = new std::vector<ClientData*>();
    }
    m_list->push_back(this);
}

ClientData* ClientData::GetClientDataBySocket(int soc)
{
    for (std::vector<ClientData*>::iterator it = m_list->begin(); it != m_list->end(); it++
         ) {
        if( (*it)->m_socket == soc )
        {
            return (*it);
        }
    }
    return nullptr;
}

ClientData* ClientData::GetClientDataByUserID(int userid)
{
    for (std::vector<ClientData*>::iterator it = m_list->begin(); it != m_list->end(); it++
         ) {
        if( (*it)->m_userID == userid )
        {
            return (*it);
        }
    }
    return nullptr;
}

ClientData::~ClientData()
{
    printf("dispose client %d\n\n", m_socket);
    delete _buff;
    if(m_list != nullptr)
    {
        delete m_list;
    }
}

void ClientData::display()
{
    printf("socket:  %d, ID: %d \n\n",m_socket,m_userID);
}

bool ClientData::write(BYTE  data[], int len)
{
    if(_buff->size() + len >= BUFF_LEN)
    {
        return false;
    }
        for (int i = 0; i < len; i++) {
            printf("data[%d]:%d \n\n",i,data[i]);
            _buff->push_back(data[i]);
        }
    return true;
}

bool ClientData::submitRead(BYTE *data, int len)
{
    //_buff->size()
    if(len > _buff->size())
    {
        return false;
    }
    
    //data = new BYTE[len];
    for (int i =0; i<len; i++) {
        data[i] = _buff->front();
        _buff->pop_front();
    }
    return  true;
}

bool ClientData::read(BYTE *data, const int len)
{
    if(len > _buff->size())
    {
        return false;
    }
    
    circular_buffer<BYTE>::iterator it = _buff->begin();
    for (int i = 0; i < len; i++) {
        data[i] = *it;
        it = it + 1;
    }
    return true;
}


