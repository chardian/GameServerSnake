//
//  RingBuffer.hpp
//  SnakeServer
//
//  Created by 查启杰 on 16/10/25.
//  Copyright © 2016年 查 启杰. All rights reserved.
//

#ifndef RingBuffer_hpp
#define RingBuffer_hpp

#include <stdio.h>
class RingBuffer
{
public:
    RingBuffer(int size);
    ~RingBuffer();
    int m_size;
};

#endif /* RingBuffer_hpp */
