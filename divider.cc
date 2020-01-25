//
//  divider.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "divider.h"

Divider::Divider(){
    monominoes.emplace_back(Cell{5, 14, 1, Colour::Brown});
    type = 'D';
    score = 0;
    count = 0;
}
