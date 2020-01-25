//
//  block.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#ifndef _BLOCK_HEADER_
#define _BLOCK_HEADER_

#include <vector>
#include <math.h>
#include "cell.h"
#include "enum.h"
#include "info.h"

class Block {
protected:
    std::vector<Cell> monominoes;
    int score;
    int count;
    char type;
    bool isHeavy;
    
    virtual void clockwise_rotate();
    virtual void shiftBlock(std::vector<int> lines);
    
public:
    Block();
    virtual void move(MoveDirection md);
    virtual void rotate(RotateDirection rd);
    virtual void clear(std::vector<int> lines);
    virtual BlockInfo getInfo();
    void reverseFillState();
    void setHeavy(bool heavy);
    virtual void calculateScore(int level);
    virtual void updateCount();
};

#endif
