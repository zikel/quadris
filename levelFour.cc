//
//  levelFour.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//
#include <cstdlib>
#include <iostream>
#include "levelFour.h"
#include "lBlock.h"
#include "jBlock.h"
#include "oBlock.h"
#include "tBlock.h"
#include "zBlock.h"
#include "sBlock.h"
#include "iBlock.h"
using namespace std;

LevelFour::LevelFour(string scriptName):
scriptName{scriptName}, next{0} {
    if (scriptName != "") {
        ifstream counterFile{scriptName};
        string s;
        int fileLen = 0;
        while (counterFile >> s) {
            ++fileLen;
        }
        len = fileLen;
    }
}

shared_ptr<Block> LevelFour::getBlock(int rn) {
    if (scriptName == "") {
        rn = rand() % 9;
        shared_ptr<Block> bp;
        if (rn < 2) {
            bp = make_shared<ZBlock>(true);
        } else if (rn < 4) {
            bp = make_shared<SBlock>(true);
        } else if (rn < 5) {
            bp = make_shared<LBlock>(true);
        } else if (rn < 6) {
            bp = make_shared<OBlock>(true);
        } else if (rn < 7) {
            bp = make_shared<IBlock>(true);
        } else if (rn < 8) {
            bp = make_shared<TBlock>(true);
        } else {
            bp = make_shared<JBlock>(true);
        }
        return bp;
    } else {
        ifstream file{scriptName};
        char type;
        int pos = 0;
        shared_ptr<Block> bp;
        while (file >> type) {
            if (pos == next){
                cout << pos << endl;
                switch(type) {
                    case 'I' : {
                        bp = make_shared<IBlock>(true);
                        break;
                    }
                    case 'J' : {
                        bp = make_shared<JBlock>(true);
                        break;
                    }
                    case 'L' :{
                        bp = make_shared<LBlock>(true);
                        break;
                    }
                    case 'O' : {
                        bp = make_shared<OBlock>(true);
                        break;
                    }
                    case 'S' : {
                        bp = make_shared<SBlock>(true);
                        break;
                    }
                    case 'Z' : {
                        bp = make_shared<ZBlock>(true);
                        break;
                    }
                    case 'T' : {
                        bp = make_shared<TBlock>(true);
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
}
