//
//  sBlock.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "sBlock.h"

SBlock::SBlock(bool heavy){
    for (int i = 0; i < 2; i++){
        monominoes.emplace_back(Cell{1 - i, 14 - i, 1, Colour::Blue});
        monominoes.emplace_back(Cell{2 - i, 14 - i, 1, Colour::Blue});
    }
    score = 0;
    type = 'S';
    count = 0;
    isHeavy = heavy;
}
