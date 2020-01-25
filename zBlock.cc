//
//  zBlock.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "zBlock.h"

ZBlock::ZBlock(bool heavy){
    for (int i = 0; i < 2; i++){
        monominoes.emplace_back(Cell{i, 14 - i, 1, Colour::Purple});
        monominoes.emplace_back(Cell{i + 1, 14 - i, 1, Colour::Purple});
    }
    score = 0;
    type = 'Z';
    count = 0;
    isHeavy = heavy;
}
