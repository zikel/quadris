//
//  hint.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-20.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#ifndef _HINT_HEADER_
#define _HINT_HEADER_

#include <vector>
#include "block.h"
#include "enum.h"
#include "cell.h"

class HintBlock: public Block {
    
public:
    HintBlock(std::vector<Cell> cells, bool heavy);
};

#endif
