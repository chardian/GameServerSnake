//
//  BitTool.hpp
//  SnakeServer
//
//  Created by 查启杰 on 17/1/2.
//  Copyright © 2017年 查 启杰. All rights reserved.
//

#ifndef BitTool_hpp
#define BitTool_hpp

#include <stdio.h>
#include "GlobalHeader.h"

class BitTool
{
public:
    static void writeInt(BYTE*, int begin, int len);
    static void writeBytes(BYTE *dest, BYTE const * src, int begin, int len);
};
#endif /* BitTool_hpp */
