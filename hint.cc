//
//  hint.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-20.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "hint.h"
using namespace std;

HintBlock::HintBlock(std::vector<Cell> cells, bool heavy) {
    type = '?';
    score = 0;
    count = 0;
    monominoes = cells;
    int minX = monominoes[0].x;
    for (auto &cell : monominoes){
        cell.colour = Colour::Black;
        if (cell.x < minX) {
            minX = cell.x;
        }
    }
    for (auto &cell : monominoes){
        cell.isFilled = true;
        cell.x -= minX;
    }
    isHeavy = heavy;
}
