//
//  iBlock.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "lBlock.h"
using namespace std;

LBlock::LBlock(bool heavy){
    monominoes.emplace_back(Cell{2, 14, 1, Colour::Orange});
    for (int i = 0; i < 3; i++){
        monominoes.emplace_back(Cell{i, 13, 1, Colour::Orange});
    }
    type = 'L';
    score = 0;
    count = 0;
    isHeavy = heavy;
}
