//
//  levelTwo.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#ifndef _LEVEL_TWO_HEADER_
#define _LEVEL_TWO_HEADER_

#include "level.h"

class LevelTwo: public Level {
    
public:
    LevelTwo();
    std::shared_ptr<Block> getBlock(int rn) override;
};

#endif
