//
//  levelZero.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//
#ifndef _LEVEL_ZERO_HEADER_
#define _LEVEL_ZERO_HEADER_
#include "level.h"
#include <string>
#include <fstream>
#include <sstream>
class LevelZero: public Level {
    std::string scriptName;
    int next;
    int len;
public:
    LevelZero(std::string scriptName);
    std::shared_ptr<Block> getBlock(int seed) override;
};
#endif
