//
//  level.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#ifndef _LEVEL_HEADER_
#define _LEVEL_HEADER_

#include <memory>
#include "block.h"

class Level {
public:
    virtual std::shared_ptr<Block> getBlock(int seed) = 0;
};

#endif
