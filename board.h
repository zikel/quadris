//
//  board.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//
#ifndef _BOARD_HEADER_
#define _BOARD_HEADER_

#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include "cell.h"
#include "block.h"
#include "enum.h"
#include "textDisplay.h"
#include "graphicalDisplay.h"
#include "level.h"
#include "info.h"
#include "subject.h"
#include <cstdlib>
class GraphicalDisplay;
class Board: public Subject {
    int level;
    std::vector<std::vector<Cell>> cells;
    std::vector<std::shared_ptr<Block>> blocks;
    std::shared_ptr<TextDisplay> td = nullptr;
    std::shared_ptr<GraphicalDisplay> gd = nullptr;
    std::shared_ptr<Level> currentLevel = nullptr;
    int highScore = 0;
    int currentScore = 0;
    std::string lvlZeroFile = "sequence.txt";
    int lvl4counter = 0;
    std::shared_ptr<Block> nextBlock;
    bool disableGraphical;
    int seed;
    int rdnum;
    bool bonusOn = false;
    
    void getFile();
    void clear();
    void updateCells();
    bool canRotate(RotateDirection rd, std::shared_ptr<Block> b);
    bool canMove(MoveDirection md, std::shared_ptr<Block> b);
    void getBlock();
    void getBlockByChar(char type);
    void dropDivider();
    int getScore();
    std::vector<int> findLinesFilled();
    void updateRdnum();
    
public:
    Board(std::string file, bool disableGraphical=false, int seed = 1);
    BoardInfo getInfo() override;
    
    void init(int level = 0);
    void changeBlock(char type);
    void rotate(RotateDirection rd, int multiples = 1);
    void move(MoveDirection md, int multiples = 1);
    void drop(int multiples = 1);
    void levelUp();
    void levelDown();
    int getLevel();
    void changeLevel(int level, std::string file);
    void getHint();
    void removeHint();
    bool isOver() const;
    void setBonus(bool isOn);
    
    friend std::ostream &operator<<(std::ostream &out, Board &b);
};

#endif
