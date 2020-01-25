//
//  levelTwo.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include <cstdlib>
#include "levelTwo.h"
#include "lBlock.h"
#include "jBlock.h"
#include "oBlock.h"
#include "tBlock.h"
#include "zBlock.h"
#include "sBlock.h"
#include "iBlock.h"

using namespace std;

LevelTwo::LevelTwo() {}

shared_ptr<Block> LevelTwo::getBlock(int rn) {
    rn = rn % 7;
    shared_ptr<Block> bp;
    if (rn < 1) {
        bp = make_shared<ZBlock>(false);
    } else if (rn < 2) {
        bp = make_shared<SBlock>(false);
    } else if (rn < 3) {
        bp = make_shared<LBlock>(false);
    } else if (rn < 4) {
        bp = make_shared<OBlock>(false);
    } else if (rn < 5) {
        bp = make_shared<IBlock>(false);
    } else if (rn < 6) {
        bp = make_shared<TBlock>(false);
    } else {
        bp = make_shared<JBlock>(false);
    }
    return bp;
}
