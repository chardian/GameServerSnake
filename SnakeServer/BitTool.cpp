//
//  BitTool.cpp
//  SnakeServer
//
//  Created by 查启杰 on 17/1/2.
//  Copyright © 2017年 查 启杰. All rights reserved.
//

#include "BitTool.hpp"

void BitTool::writeInt(BYTE* buff, int begin, int len)
{
    buff[begin] = len;
    buff[begin + 1] = len >> 8;
    buff[begin + 2] = len >> 16;
    buff[begin + 3] = len>>24;
}

void BitTool::writeBytes(BYTE *dest, BYTE const *src, int begin, int len)
{
    for (int i = 0; i < len; i++) {
        dest[begin + i] = src[i];
    }
}


