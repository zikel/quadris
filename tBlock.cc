//
//  tBlock.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "tBlock.h"

TBlock::TBlock(bool heavy){
    for (int i = 0; i < 3; i++){
        monominoes.emplace_back(Cell{i, 14, 1, Colour::Teal});
    }
    monominoes.emplace_back(Cell{1, 13, 1, Colour::Teal});
    score = 0;
    type = 'T';
    count = 0;
    isHeavy = heavy;
}
