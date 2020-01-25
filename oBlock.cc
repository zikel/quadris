//
//  oBlock.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "oBlock.h"
using namespace std;

OBlock::OBlock(bool heavy){
    for (int i = 0; i < 2; i++){
        monominoes.emplace_back(Cell{0, 14 - i, 1, Colour::Green});
        monominoes.emplace_back(Cell{1, 14 - i, 1, Colour::Green});
    }
    type = 'O';
    score = 0;
    count = 0;
    isHeavy = heavy;
}
