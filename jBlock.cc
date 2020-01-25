
//
//  jBlock.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "jBlock.h"
using namespace std;

JBlock::JBlock(bool heavy){
    monominoes.emplace_back(Cell{0, 14, 1, Colour::Yellow});
    for (int i = 0; i < 3; i++){
        monominoes.emplace_back(Cell{i, 13, 1, Colour::Yellow});
    }
    type = 'J';
    score = 0;
    count = 0;
    isHeavy = heavy;
}
