//
//  main.cpp
//  SnakeServer
//
//  Created by 查启杰 on 16/10/13.
//  Copyright © 2016年 查 启杰. All rights reserved.
//

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include "qi.pb.h"
#include "ClientData.h"
#include <map>
#include <boost/circular_buffer.hpp>
#include <unistd.h>
#include <stdlib.h>
#include "MessageController.hpp"



static std::map<int,ClientData*> *m_clients;
void recvThread(ClientData *,int a);
void* sendThread(void *);
const char* CHR_IP = "192.168.0.103";

void test()
{
 /*   Node *n = new Node();
    n->set_x(333);
    n->set_y(980);
    int len = sizeof(Node) + 1;
    char buff[sizeof(Node) + 1] = {0};
    n->SerializeToArray(buff,len);
    Node * j = new Node();
    j->ParseFromArray(buff, len);
    printf("x:%d,y:%d\n\n",j->x(), j->y());*/
    
    boost::circular_buffer<char> b(3);
    b.push_back('a');
    b.push_back('b');
    b.push_back('c');
    boost::circular_buffer<char>::iterator it;
    for (it = b.begin(); it != b.end(); it++) {
        printf("mmmm is : %c\n\n", *it);
    }
    char m = b.front();
    printf("ii %c",m);
    b.pop_front();

    m = b.front();
    printf("jj %c",m);
    b.pop_front();
    
    m = b.front();
    printf("kk %c",m);
    b.pop_front();
    
}

void test1()
{
    BYTE bbb[] = {7,0,0,0};
    int a = *(int*)bbb;
    printf("huake is %d \n\n", a);
}

int clients[10];
fd_set fs;

int main(int argc, const char * argv[]) {
    //test1();
    //return 0;
    m_clients = new std::map<int,ClientData*>();
    struct sockaddr_in server_addr;
    server_addr.sin_len = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8830);
    server_addr.sin_addr.s_addr = inet_addr(CHR_IP);
    bzero(&(server_addr.sin_zero), 8);
    int soc = socket(AF_INET, SOCK_STREAM, 0);
    if(soc == -1)
    {
        printf("what the fuck\n\n");
        exit(EXIT_FAILURE);
    }else
    {
        printf("create successfully!\n\n");
    }
    
    //这两行抄来的
    int opt = 1;
    setsockopt(soc,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
    
    //会跟std::bind冲突啊.
    int bind_result = ::bind(soc, (struct sockaddr*)&server_addr,sizeof(server_addr));
    if(bind_result == -1)
    {
        perror("fuck you bind error?\n\n");
        exit(EXIT_FAILURE);
    }else
    {
        printf("ok bind ok\n\n");
    }
    int listen_ret = listen(soc, 100);
    if(listen_ret == -1)
    {
        perror("listen error\n\n");
        exit(EXIT_FAILURE);
    }else
    {
        printf("okok listene\n\n");
    }
    
    int max_fd = -1;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    
    while(true)
    {
        __DARWIN_FD_ZERO(&fs);
        __DARWIN_FD_SET(soc, &fs);
        max_fd = soc;
        for (int i = 0; i < 10; i++) {
            if(clients[i] > 0)
            {
                __DARWIN_FD_SET(clients[i], &fs);
                if(max_fd < clients[i])
                {
                    max_fd = clients[i];
                }
            }
        }
        //printf("max fd is %d\n\n",max_fd);
        int ret = select(max_fd + 1, &fs, NULL, NULL, &tv);
        if(ret <0)
        {
            printf("select errorno: %d \n",errno);
        }else if(ret == 0)
        {
            
        }else
        {
            if(__DARWIN_FD_ISSET(soc, &fs))
            {
                struct sockaddr_in client_address;
                socklen_t address_len;
                printf("start to accept now \n\n");
                int c_soc = accept(soc, (struct sockaddr *)&client_address, &address_len);
                int inx = -1;
                for (int i = 0; i < 10; i++) {
                    if(clients[i] == 0)
                    {
                        inx = i;
                        clients[i] = c_soc;
                        break;
                    }
                }
                if(inx >= 0)
                {
                    printf("welcome new clients\n\n");
                    ClientData *cd = new ClientData(c_soc);
                    m_clients->insert(std::pair<int, ClientData*>(c_soc, cd));
                }
            }
            for (int i = 0; i < 10; i++) {
                if(clients[i] > 0)
                {
                    if(__DARWIN_FD_ISSET(clients[i], &fs))
                    {
                        //bzero(recv_msg, BUFF_SIZE);
                        //int recvret = recv(clients[i], recv_msg, BUFF_SIZE, 0);
                        ClientData* cd = (*m_clients)[clients[i]];
                        recvThread(cd, i);
                    }
                }
                
            }
        }
        
        /*struct sockaddr_in client_address;
        socklen_t address_len;
        printf("start to accept now \n\n");
        int client_socket = accept(soc, (struct sockaddr *)&client_address, &address_len);
        
        if(client_socket == -1)
        {
            perror("fuck you accept error\n\n");
        }else
        {
            printf("get a client !!! %d\n\n", client_socket);
        }
        pthread_t tid;
        pthread_create(&tid, NULL, recvThread, (void*)&client_socket);
        ClientData *ct = new ClientData(client_socket);
        //map要使用Insert方法, 否则长度只会有2, 而且还不会报错.
        m_clients->insert(std::pair<int,ClientData*>(client_socket, ct));*/
    }
    
    return 0;
}


void *sendThread(void *arg)
{
    int *p = (int*)(arg);
    int server_socket = *p;
    
    return  NULL;
}

BYTE recv_msg[1024];
void recvThread(ClientData *ct, int i)
{
    //int *p = (int*)(arg);
    //int client_socket = *p;
    //ClientData* ct = (*m_clients)[client_socket];
    if(ct == NULL)
    {
        printf("socket is %d\n\n",ct->m_socket);
    }else
    {
        ct->display();
    }
    
    bzero(recv_msg, 1024);
        printf("get data now from %d\n\n", ct->m_socket);
    bzero(recv_msg, 1024);
    ssize_t n = recv(ct->m_socket, recv_msg, 1024, 0);
        if(n == 0)
        {
            //clients[i] = 0;设置为零说明这个连接已经不能再使用了.
            printf("over now\n\n");
            clients[i] = 0;
            return;
        }
        //个人接收数据,每个人维护一个数组, 用来存储接收到的数据.
        bool ret = ct->write(recv_msg, n);
        int totalLen = ct->getBufferLen();
        printf("total len is %d\n\n", totalLen);
    
    printf("got %s \n\n",recv_msg);
        if(totalLen > 8)
        {
            BYTE byteSizeLen[4];
            BYTE byteMsgID[4];
            ct->read(byteSizeLen, 4);
            int* p = (int*)byteSizeLen;
            printf("array is %d,%d,%d,%d\n\n",byteSizeLen[0],byteSizeLen[1],byteSizeLen[2],byteSizeLen[3]);
            printf("size of content is %d\n\n", *p);
            //assert(*p > 999999);//满足条件就跳出来， 数据出错了.这代码写了也没什么意思。
            int msgSize = *p;
            int msgID;
            //ct->read(byteMsgID,4);
            //p = (int*)byteMsgID;
            //int msgID = *p;
            
            if(totalLen > 8)
            {
                
                //已经够用来读取数据了
                ct->submitRead(byteSizeLen, 4);
                ct->submitRead(byteMsgID, 4);
                msgID = *(int*)byteMsgID;
                
                BYTE* msgData = new BYTE[msgSize];
                ct->submitRead(msgData, msgSize);
                
                printf("size %d, %s \n\n",msgSize, msgData);
                //LoginReq* req = new LoginReq();
                //req->ParseFromArray(msgData, msgSize);
                //printf("name is %s ,proto id is: %d\n\n", req->name().c_str(), req->proid());
                MESSAGE_DATA md;
                md.msgID = msgID;
                md.msgLen = msgSize;
                md.msgData = msgData;
                md.socket = ct->m_socket;
                MessageController::Instance()->addRecv(md);
                
                
                
            }
            
        printf("%d: %s \n\n" , ct->m_socket,recv_msg);
    }
}

