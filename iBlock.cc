//
//  IBlock.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "iBlock.h"
using namespace std;

IBlock::IBlock(bool heavy){
    for (int i = 0; i < 4; i++){
        monominoes.emplace_back(Cell{i, 14, 1, Colour::Red});
    }
    type = 'I';
    score = 0;
    count = 0;
    isHeavy = heavy;
}
