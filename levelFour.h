//
//  levelFour.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//
#ifndef _LEVEL_FOUR_HEADER_
#define _LEVEL_FOUR_HEADER_
#include "level.h"
#include <string>
#include <fstream>
#include <sstream>
class LevelFour: public Level {
    std::string scriptName;
    int next;
    int len;
public:
    LevelFour(std::string scriptName);
    std::shared_ptr<Block> getBlock(int rn) override;
};
#endif
