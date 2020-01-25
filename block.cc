//
//  block.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "block.h"
using namespace std;

Block::Block(){}

void Block::move(MoveDirection md){
    switch (md) {
        case MoveDirection::Left: {
            for (size_t i = 0; i < monominoes.size(); i++) {
                monominoes[i].x--;
            }
            break;
        } case MoveDirection::Right: {
            for (size_t i = 0; i < monominoes.size(); i++) {
                monominoes[i].x++;
            }
            break;
        } case MoveDirection::Down: {
            for (size_t i = 0; i < monominoes.size(); i++) {
                monominoes[i].y--;
            }
            break;
        } default: {
            break;
        }
    }
}

void Block::rotate(RotateDirection rd) {
    if (rd == RotateDirection::Clockwise) {
        clockwise_rotate();
    } else {
        for (int i = 0; i < 3; ++i) {
            clockwise_rotate();
        }
    }
}


void Block::clockwise_rotate() {
    Cell bottom_left = monominoes.at(0);
    Cell bottom_right = monominoes.at(0);
    for (const auto &cell : monominoes) {
        bottom_left.x = min(bottom_left.x, cell.x);
        bottom_left.y = min(bottom_left.y, cell.y);
        bottom_right.x = max(bottom_right.x, cell.x);
        bottom_right.y = min(bottom_right.y, cell.y);
    }
    
    for (auto &cell : monominoes) {
        int x_offset = cell.x - bottom_right.x;
        int y_offset = cell.y - bottom_right.y;
        cell.x = bottom_left.x + y_offset;
        cell.y = bottom_left.y - x_offset;
    }
}

void Block::clear(vector<int> lines){
    for (auto &line : lines) {
        vector<Cell> temp;
        for (auto &cell : monominoes) {
            if (cell.y != line) {
                temp.emplace_back(cell);
            }
        }
        monominoes = temp;
    }
    shiftBlock(lines);
}

void Block::shiftBlock(vector<int> lines){
    for (auto &cell : monominoes) {
        int counter = 0;
        for (auto &line : lines) {
            if (cell.y > line) {
                counter++;
            }
        }
        for (int i = 0; i < counter; i++) {
            cell.y--;
        }
    }
}

BlockInfo Block::getInfo(){
    return BlockInfo{monominoes, type, score, count, isHeavy};
}

void Block::calculateScore(int level) {
    score = pow(level + 1, 2);
}

void Block::updateCount(){
    count++;
}

void Block::reverseFillState(){
    for (auto &cell: monominoes){
        cell.isFilled = !cell.isFilled;
    }
}
void Block::setHeavy(bool heavy){
    isHeavy = heavy;
}
