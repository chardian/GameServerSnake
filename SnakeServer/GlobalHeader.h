//
//  GlobalHeader.h
//  SnakeServer
//
//  Created by 查启杰 on 16/10/18.
//  Copyright © 2016年 查 启杰. All rights reserved.
//

#ifndef GlobalHeader_h
#define GlobalHeader_h
typedef unsigned char BYTE;
//circle length
const int BUFF_LEN = 1024 * 64;

//message size
#define BUFF_SIZE 1024

typedef struct
{
    int socket;
    int msgLen;
    int msgID;
    BYTE* msgData;
}MESSAGE_DATA;

enum UserState
{
    STATE_NOT_READY,
    STATE_READY,
    STATE_MY_TURN,
    STATE_OTHER_TURN,
    STATE_GAME_OVER
};

const int MAX_ROOM = 10;

#endif /* GlobalHeader_h */
