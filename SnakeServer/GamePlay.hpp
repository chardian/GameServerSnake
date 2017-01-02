//
//  GamePlay.hpp
//  SnakeServer
//
//  Created by 查启杰 on 16/10/16.
//  Copyright © 2016年 查 启杰. All rights reserved.
//

#ifndef GamePlay_hpp
#define GamePlay_hpp

#include "qi.pb.h"
#include <map>
using namespace std;

#include <stdio.h>
class GamePlay
{
public:
    static GamePlay *getInstance();
    GamePlay();
    ~GamePlay();
    void display();
private:
    //all snakes
    //map<int,Snake> m_snakes;
    
};
#endif /* GamePlay_hpp */
