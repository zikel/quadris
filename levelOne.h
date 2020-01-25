//
//  levelOne.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#ifndef _LEVEL_ONE_HEADER_
#define _LEVEL_ONE_HEADER_

#include "level.h"

class LevelOne: public Level {
    
public:
    LevelOne();
    std::shared_ptr<Block> getBlock(int rn) override;
};

#endif
