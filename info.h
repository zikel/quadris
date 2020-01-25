//
//  info.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#ifndef _INFO_HEADER_
#define _INFO_HEADER_


#include <vector>
#include <memory>
#include "enum.h"

class Block;
class Board;
struct Cell;

struct BoardInfo {
    int currentScore, highScore, level;
    std::vector<std::shared_ptr<Block>> b;
    std::vector<std::vector<Cell>> cells;
    std::shared_ptr<Block> next;
};

struct BlockInfo {
    std::vector<Cell> cells;
    char type;
    int score, count;
    bool isHeavy;
};

#endif
