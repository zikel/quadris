//
//  levelZero.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//
#include "levelZero.h"
#include "iBlock.h"
#include "lBlock.h"
#include "jBlock.h"
#include "oBlock.h"
#include "tBlock.h"
#include "zBlock.h"
#include "sBlock.h"
#include <iostream>
using namespace std;
LevelZero::LevelZero(string scriptName):
scriptName{scriptName}, next{0} {
    ifstream counterFile{scriptName};
    string s;
    int fileLen = 0;
    while (counterFile >> s) {
        ++fileLen;
    }
    len = fileLen;
}
shared_ptr<Block> LevelZero::getBlock(int seed) {
    ifstream file{scriptName};
    char type;
    int pos = 0;
    shared_ptr<Block> bp;
    
    while (file >> type) {
        if (pos == next){
            switch(type) {
                case 'I' : {
                    bp = make_shared<IBlock>(false);
                    break;
                }
                case 'J' : {
                    bp = make_shared<JBlock>(false);
                    break;
                }
                case 'L' :{
                    bp = make_shared<LBlock>(false);
                    break;
                }
                case 'O' : {
                    bp = make_shared<OBlock>(false);
                    break;
                }
                case 'S' : {
                    bp = make_shared<SBlock>(false);
                    break;
                }
                case 'Z' : {
                    bp = make_shared<ZBlock>(false);
                    break;
                }
                case 'T' : {
                    bp = make_shared<TBlock>(false);
                    break;
                }
            }
            break;
        }
        pos++;
    }
    next++;
    if (next == len) {
        next = 0;
    }
    return bp;
}
