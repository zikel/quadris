//
//  textDisplay.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#ifndef _TEXT_DISPLAY_HEADER_
#define _TEXT_DISPLAY_HEADER_

#include <vector>
#include "observer.h"
#include <iostream>
#include <iomanip>
#include "block.h"
class Board;

const int width = 11;
const int height = 18;

class TextDisplay: public Observer {
    std::vector<std::vector<char>> textDisplay;
    int highScore;
    int currentScore;
    int level;
    std::shared_ptr<Block> nextBlock;
    
    void newDisplay();
    
public:
    TextDisplay();
    void notify(Subject &b) override;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
