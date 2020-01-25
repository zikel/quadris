//
//  board.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include <utility>
#include <algorithm>
#include <math.h>
#include <map>
#include "board.h"
#include "iBlock.h"
#include "jBlock.h"
#include "oBlock.h"
#include "tBlock.h"
#include "lBlock.h"
#include "zBlock.h"
#include "sBlock.h"
#include "divider.h"
#include "hint.h"
#include "levelZero.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"

using namespace std;

Board::Board(string file, bool disableGraphical, int seed):
td{make_shared<TextDisplay>()}, gd{}, lvlZeroFile{file},
disableGraphical{disableGraphical}, seed{seed} {
    attach(dynamic_pointer_cast<Observer>(td));
    if (!disableGraphical){
        gd = make_shared<GraphicalDisplay>();
        attach(dynamic_pointer_cast<Observer>(gd));
    }
}


BoardInfo Board::getInfo(){
    return BoardInfo{currentScore, highScore, level,
        blocks, cells, nextBlock};
}

bool Board::isOver() const{
    vector<Cell> cells = blocks.back()->getInfo().cells;
    for(size_t i = 0; i < blocks.size() - 1; i++){
        for (const auto &c : blocks.at(i)->getInfo().cells) {
            if (find_if(cells.begin(), cells.end(),
                        [c] (const Cell &rhs) {
                            return c.x == rhs.x && c.y == rhs.y;})
                != cells.end()) {
                return true;
            }
        }
    }
    return false;
}

void Board::clear(){
    vector<int> linesFilled = findLinesFilled();
    if (!linesFilled.empty()){
        lvl4counter++;
        for(size_t i = 0; i < blocks.size(); i++){
            blocks[i]->clear(linesFilled);
            if (blocks[i]->getInfo().cells.empty()) {
                currentScore += blocks[i]->getInfo().score;
                blocks.erase(blocks.begin() + i);
                i--;
                continue;
            }
        }
        currentScore += pow(level + linesFilled.size(), 2);
        if (currentScore > highScore) {
            highScore = currentScore;
        }
    }
    
    if (bonusOn) {
        for (size_t i = 0; i < blocks.size(); i++){
            if (blocks[i]->getInfo().count > 10 && level == 4
                && blocks[i]->getInfo().type != 'D'
                && blocks[i]->getInfo().type != '?'){
                blocks.erase(blocks.begin() + i);
                i--;
            }
        }
    }
}

vector<int> Board::findLinesFilled(){
    
    bool isCleared = true;
    vector<int> lineFilled;
    for (int i = 0; i < height; i++){
        for(auto &column : cells){
            if (column[i].isFilled == false) isCleared = false;
        }
        if (isCleared){
            lineFilled.emplace_back(i);
        }
        isCleared = true;
    }
    return lineFilled;
}

void Board::init(int level){
    srand(seed);
    updateRdnum();
    switch(level) {
        case 0 : currentLevel = make_shared<LevelZero>(lvlZeroFile);
            this->level = 0;
            break;
        case 1 : currentLevel = make_shared<LevelOne>();
            this->level = 1;
            break;
        case 2 : currentLevel = make_shared<LevelTwo>();
            this->level = 2;
            break;
        case 3 : currentLevel = make_shared<LevelThree>("");
            this->level = 3;
            break;
        case 4 : currentLevel = make_shared<LevelFour>("");
            this->level = 4;
            break;
            
        default:
            break;
    }
    cells = vector<vector<Cell>>{};
    for(int i = 0; i < width; i++){
        vector<Cell> column;
        vector<Cell> prevcolumn;
        for(int j = 0; j < height; j++){
            column.emplace_back(Cell{i, j, false, Colour::White});
        }
        cells.emplace_back(column);
    }
    currentScore = 0;
    blocks.clear();
    nextBlock = currentLevel->getBlock(rdnum);
    updateRdnum();
    getBlock();
}


bool Board::canRotate(RotateDirection rd, shared_ptr<Block>b){
    vector<Cell> currentCells = b->getInfo().cells;
    b->rotate(rd);
    
    for(auto &cell : b->getInfo().cells){
        if (cell.x < 0 || cell.x > 10 ||
            cell.y < 0 || cell.y > 17){
            return false;
        }
        if (cells[cell.x][cell.y].isFilled &&
            find(currentCells.begin(), currentCells.end(),
                 cells[cell.x][cell.y])
            == currentCells.end()){
            return false;
        }
    }
    return true;
}


void Board::rotate(RotateDirection rd, int multiples){
    shared_ptr<Block> rotateB = blocks.back();
    for(int i = 0; i < multiples; i++){
        if (!canRotate(rd, rotateB)){
            RotateDirection newRd = (rd == RotateDirection::Clockwise ?
                                     RotateDirection::CounterClockwise :
                                     RotateDirection::Clockwise);
            rotateB->rotate(newRd);
        }
        updateCells();
    }
    updateCells();
    if (blocks.back()->getInfo().isHeavy &&
        canMove(MoveDirection::Down, rotateB)){
        rotateB->move(MoveDirection::Down);
        updateCells();
    }
    
    if (rotateB->getInfo().type != '?') {
        notifyObservers();
        cout << *this;
    }
}




bool Board::canMove(MoveDirection md, shared_ptr<Block> b){
    vector<Cell> currentCells = b->getInfo().cells;
    if (md == MoveDirection::Left){
        for(auto &cell : currentCells){
            if (cell.x - 1 < 0) return false;
            const Cell movedCell = cells[cell.x - 1][cell.y];
            if (find(currentCells.begin(), currentCells.end(), movedCell)
                == currentCells.end() && movedCell.isFilled){
                return false;
            }
        }
    } else if (md == MoveDirection::Right){
        for(auto &cell : currentCells){
            if (cell.x + 1 > 10) return false;
            const Cell movedCell = cells[cell.x + 1][cell.y];
            if (find(currentCells.begin(), currentCells.end(), movedCell)
                == currentCells.end() && movedCell.isFilled){
                return false;
            }
        }
    } else{
        for(auto &cell : currentCells){
            if (cell.y - 1 < 0) return false;
            const Cell movedCell = cells[cell.x][cell.y - 1];
            if (find(currentCells.begin(), currentCells.end(), movedCell)
                == currentCells.end()
                && movedCell.isFilled){
                return false;
                
            }
        }
        
    }
    return true;
}

void Board::move(MoveDirection md, int multiples){
    shared_ptr<Block> moveB = blocks.back();
    for(int i = 0; i < multiples; i++){
        if (canMove(md, moveB)){
            moveB->move(md);
            updateCells();
        }
    }
    if (blocks.back()->getInfo().isHeavy &&
        canMove(MoveDirection::Down, moveB) ){
        moveB->move(MoveDirection::Down);
        updateCells();
    }
    if (moveB->getInfo().type != '?') {
        notifyObservers();
        cout << *this;
    }
}

void Board::updateCells(){
    
    for(auto &column: cells){
        for(auto &cell : column){
            cell.isFilled = false;
            cell.colour = Colour::White;
        }
    }
    for (auto &block : blocks) {
        if (block) {
            for(auto &filledCell : block->getInfo().cells){
                int x = filledCell.x;
                int y = filledCell.y;
                cells[x][y].isFilled = filledCell.isFilled;
                cells[x][y].colour = filledCell.colour;
            }
        }
    }
}

void Board::dropDivider(){
    if (level == 4 && lvl4counter%5 == 0 && lvl4counter != 0){
        blocks.emplace_back(make_shared<Divider>());
        shared_ptr<Block> dropB = blocks.back();
        while(canMove(MoveDirection::Down, dropB)){
            blocks.back()->move(MoveDirection::Down);
        }
        updateCells();
    }
}


void Board::drop(int multiples){
    for(int i = 0; i < multiples; i++){
        lvl4counter++;
        shared_ptr<Block> dropB = blocks.back();
        while(canMove(MoveDirection::Down, dropB)){
            blocks.back()->move(MoveDirection::Down);
        }
        updateCells();
        clear();
        updateCells();
        dropDivider();
        clear();
        getBlock();
    }
}


void Board::getBlock(){
    nextBlock->calculateScore(level);
    blocks.emplace_back(nextBlock);
    blocks.back()->setHeavy(level > 2);
    nextBlock = currentLevel->getBlock(rdnum);
    updateRdnum();
    for (auto &block: blocks){
        block->updateCount();
    }
    updateCells();
    notifyObservers();
    cout << *this;
}

void Board::getBlockByChar(char type){
    switch(type) {
        case 'I' : blocks.emplace_back(make_shared<IBlock>(level > 2));
            break;
        case 'J' : blocks.emplace_back(make_shared<JBlock>(level > 2));
            break;
        case 'L' : blocks.emplace_back(make_shared<LBlock>(level > 2));
            break;
        case 'O' : blocks.emplace_back(make_shared<OBlock>(level > 2));
            break;
        case 'S' : blocks.emplace_back(make_shared<SBlock>(level > 2));
            break;
        case 'Z' : blocks.emplace_back(make_shared<ZBlock>(level > 2));
            break;
        case 'T' : blocks.emplace_back(make_shared<TBlock>(level > 2));
            break;
    }
}

void Board::changeBlock(char type){
    vector<Cell> cells = blocks.back()->getInfo().cells;
    for(auto &cell : cells){
        int x = cell.x;
        int y = cell.y;
        this->cells[x][y].isFilled = false;
    }
    blocks.pop_back();
    getBlockByChar(type);
    blocks.back()->calculateScore(level);
    updateCells();
    notifyObservers();
    cout << *this;
}


void Board::levelUp(){
    if(level >= 0 && level < 4){
        switch(level){
            case 0 : currentLevel = make_shared<LevelOne>();
                break;
            case 1 : currentLevel = make_shared<LevelTwo>();
                break;
            case 2 : currentLevel = make_shared<LevelThree>("");
                break;
            case 3 : currentLevel = make_shared<LevelFour>("");
                lvl4counter = 0;
                break;
        }
        level++;
        notifyObservers();
        cout << *this;
    }
}

void Board::levelDown(){
    if(level <= 4 && level > 0){
        switch(level){
            case 1 : currentLevel = make_shared<LevelZero>(lvlZeroFile);
                break;
            case 2 : currentLevel = make_shared<LevelOne>();
                break;
            case 3 : currentLevel = make_shared<LevelTwo>();
                break;
            case 4 : currentLevel = make_shared<LevelThree>("");
                break;
        }
        level--;
        notifyObservers();
        cout << *this;
    }
}


int Board::getLevel(){
    return level;
}

void Board::getHint(){
    blocks.back()->reverseFillState();
    bool isPreviousHeavy = blocks.back()->getInfo().isHeavy;
    blocks.emplace_back(make_shared<HintBlock>
                        (blocks.back()->getInfo().cells, false));
    updateCells();
    blocks.back()->setHeavy(isPreviousHeavy);
    
    int score = -100;
    int bestMove = 0;
    int bestDown = 0;
    int bestRotate = 0;
    int moveRight = 0;
    
    int right = 0;
    int down = 0;
    for (int i = 0; i < 4; i++){
        
        blocks.pop_back();
        blocks.emplace_back(make_shared<HintBlock>
                            (blocks.back()->getInfo().cells, false));
        
        int j = i;
        while (j > 0){
            rotate(RotateDirection::Clockwise);
            j--;
        }
        right = 0;
        down = 0;
        for (int k = 0; k < height; k++){
            for (int l = 0; l < width; l++){
                int s = getScore();
                if ((score == -100 || s > score) &&
                    !canMove(MoveDirection::Down, blocks.back())){
                    score = s;
                    bestMove = right;
                    bestDown = down;
                    bestRotate = i;
                    moveRight = 1;
                }
                
                int oriX = blocks.back()->getInfo().cells[0].x;
                move(MoveDirection::Right);
                if (oriX != blocks.back()->getInfo().cells[0].x){
                    right++;
                }
            }
            int oriY = blocks.back()->getInfo().cells[0].y;
            move(MoveDirection::Down);
            if (oriY != blocks.back()->getInfo().cells[0].y) {
                down++;
            }
            while (right > 0) {
                int oriX = blocks.back()->getInfo().cells[0].x;
                move(MoveDirection::Left);
                if (oriX != blocks.back()->getInfo().cells[0].x) {
                    right--;
                } else {
                    break;
                }
            }
        }
    }
    
    int left = 0;
    down = 0;
    for (int i = 0; i < 4; i++){
        
        blocks.pop_back();
        blocks.emplace_back(make_shared<HintBlock>
                            (blocks.back()->getInfo().cells, false));
        
        for (int p = 0; p < width; p++){
            move(MoveDirection::Right);
        }
        
        int j = i;
        while (j > 0){
            rotate(RotateDirection::Clockwise);
            j--;
        }
        left = 0;
        down = 0;
        for (int k = 0; k < height; k++){
            for (int l = 0; l < width; l++){
                int s = getScore();
                if ((score == -100 || s > score) &&
                    !canMove(MoveDirection::Down, blocks.back())){
                    score = s;
                    bestMove = left;
                    bestDown = down;
                    bestRotate = i;
                    moveRight = 0;
                }
                
                int oriX = blocks.back()->getInfo().cells[0].x;
                move(MoveDirection::Left);
                if (oriX != blocks.back()->getInfo().cells[0].x){
                    left++;
                }
            }
            int oriY = blocks.back()->getInfo().cells[0].y;
            move(MoveDirection::Down);
            if (oriY != blocks.back()->getInfo().cells[0].y) {
                down++;
            }
            while (left > 0) {
                int oriX = blocks.back()->getInfo().cells[0].x;
                move(MoveDirection::Right);
                if (oriX != blocks.back()->getInfo().cells[0].x) {
                    left--;
                } else {
                    break;
                }
            }
        }
    }
    
    int newDown = 0;
    int newRight = 0;
    for (int i = 0; i < 4; i++){
        
        blocks.pop_back();
        blocks.emplace_back(make_shared<HintBlock>
                            (blocks.back()->getInfo().cells, false));
        
        int j = i;
        while (j > 0){
            rotate(RotateDirection::Clockwise);
            j--;
        }
        newRight = 0;
        newDown = 0;
        for (int k = 0; k < width; k++){
            for (int l = 0; l < height; l++){
                int s = getScore();
                if ((score == -100 || s > score) &&
                    !canMove(MoveDirection::Down, blocks.back())){
                    score = s;
                    bestMove = newRight;
                    bestDown = newDown;
                    bestRotate = i;
                    moveRight = 1;
                }
                
                int oriX = blocks.back()->getInfo().cells[0].y;
                move(MoveDirection::Down);
                if (oriX != blocks.back()->getInfo().cells[0].y){
                    newDown++;
                }
            }
            int oriY = blocks.back()->getInfo().cells[0].x;
            move(MoveDirection::Right);
            if (oriY != blocks.back()->getInfo().cells[0].x) {
                newRight++;
            }
        }
    }
    
    blocks.pop_back();
    blocks.emplace_back(make_shared<HintBlock>
                        (blocks.back()->getInfo().cells, false));
    
    while (bestRotate > 0){
        rotate(RotateDirection::Clockwise);
        bestRotate--;
    }
    
    if (moveRight == 1) {
        while (bestMove > 0) {
            move(MoveDirection::Right);
            bestMove--;
        }
    } else if (moveRight == 0){
        for (int p = 0; p < width; p++){
            move(MoveDirection::Right);
        }
        while (bestMove > 0) {
            move(MoveDirection::Left);
            bestMove--;
        }
    }
    
    while (bestDown > 0) {
        move(MoveDirection::Down);
        bestDown--;
    }
    
    notifyObservers();
    cout << *this;
}

int Board::getScore(){
    int score = 0;
    vector<int> linesFilled = findLinesFilled();
    size_t index = linesFilled.size();
    while (index > 0){
        score += 100;
        index--;
    }
    
    for (auto &cell: blocks.back()->getInfo().cells) {
        if (cell.y == 0) {
            score += 10;
        } else if (cells[cell.x][cell.y - 1].isFilled == false){
            score -= 15;
        }
    }
    score -= blocks.back()->getInfo().cells[0].y;
    score -= blocks.back()->getInfo().cells[0].x / 10;
    return score;
}

void Board::removeHint(){
    if (blocks.back()->getInfo().type == '?'){
        blocks.pop_back();
        blocks.back()->reverseFillState();
        updateCells();
    }
}

void Board::changeLevel(int level, string file){
    if (level == 3){
        currentLevel = make_shared<LevelThree>(file);
    } else {
        currentLevel = make_shared<LevelFour>(file);
    }
    notifyObservers();
    cout << *this;
}

void Board::updateRdnum() {
    rdnum = rand();
}

void Board::setBonus(bool isOn){
    bonusOn = isOn;
}

ostream &operator<<(ostream &out, Board &b){
    out << *(b.td);
    return out;
}


