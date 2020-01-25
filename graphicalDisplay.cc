#include "graphicalDisplay.h"
#include <iostream>
using namespace std;

GraphicalDisplay::GraphicalDisplay(): window{Xwindow()}{

    window.fillRectangle(130, 10, 5, 550, Xwindow::Black);
    window.fillRectangle(130, 10, 335, 5, Xwindow::Black);
    window.fillRectangle(130, 555, 335, 5, Xwindow::Black);
    window.fillRectangle(465, 10, 5, 550, Xwindow::Black);
    window.drawBigString(15, 50, "QUADRIS");
    window.drawString(20, 80, "Level:");
    window.drawString(20, 100, "Score:");
    window.drawString(20, 120, "Hi Score:");
    window.drawString(100, 80, "0");
    window.drawString(100, 100, "0");
    window.drawString(100, 120, "0");

    prevBoard.cells = vector<vector<Cell>>{};

    for(int i = 0; i < 11; i++){
        vector<Cell> column;
        for(int j = 0; j < 18; j++){
            column.emplace_back(Cell{i, j, false, Colour::White});
        }
        prevBoard.cells.emplace_back(column);
    }
}

void GraphicalDisplay::fillCell(int x, int y, int cellSize, Colour colour){
    switch(colour) {
        case Colour::Black : window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Black);
            break;
        case Colour::Brown : window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Brown);
            break;
        case Colour::Red : window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Red);
            break;
        case Colour::Orange : window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Orange);
            break;
        case Colour::Yellow : window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Yellow);
            break;
        case Colour::Green : window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Green);
            break;
        case Colour::Blue : window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Blue);
            break;
        case Colour::Purple : window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Purple);
            break;
        case Colour::Teal : window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Teal);
            break;

        default:
            window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
            break;
    }
}

void GraphicalDisplay::notify(Subject &whoNotified){
    BoardInfo board = whoNotified.getInfo();
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 18; j++){
            if (!(board.cells[i][j] == prevBoard.cells[i][j])){
                fillCell(135 + i * 30,
                         15+(17-j) * 30,
                         30, board.cells[i][j].colour);
            }
        }
    }

    ostringstream oss;
    string output;
    if (prevBoard.level != board.level){
        window.fillRectangle(100, 70, 10, 10, Xwindow::White);
        oss << board.level;
        output = oss.str();
        window.drawString(100, 80, output);
    }

    if (prevBoard.currentScore != board.currentScore){
        window.fillRectangle(100, 90, 30, 10, Xwindow::White);
        oss.str("");
        oss << board.currentScore;
        output = oss.str();
        window.drawString(100, 100,output);
    }

    if (prevBoard.highScore != board.highScore){
        window.fillRectangle(100, 110, 30, 10, Xwindow::White);
        oss.str("");
        oss << board.highScore;
        output = oss.str();
        window.drawString(100, 120, output);
    }

    prevBoard = board;
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 2; y++){
            fillCell(20 + x * 20, 250 +
                     y * 20, 20, Colour::White);
        }
    }


    for(int i = 0; i < 4; i++){
        BlockInfo block = board.next->getInfo();
        window.drawString(20, 240, "Next:");
        fillCell(20 + block.cells[i].x * 20,
                 250 + (14 - block.cells[i].y) * 20, 20,
                 block.cells[i].colour);
    }
}



