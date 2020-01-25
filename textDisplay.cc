//
//  textDisplay.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "textDisplay.h"
#include "subject.h"
using namespace std;

TextDisplay::TextDisplay(){
    for(int i = 0; i < width; i++){
        vector<char> row;
        for(int j = 0; j < height; j++){
            row.emplace_back(' ');
        }
        textDisplay.emplace_back(row);
    }
}

void TextDisplay::newDisplay(){
    for(auto &row : textDisplay){
        for(auto &cell : row){
            cell = ' ';
        }
    }
}

void TextDisplay::notify(Subject &b){
    newDisplay();
    BoardInfo info = b.getInfo();
    highScore = info.highScore;
    currentScore = info.currentScore;
    level = info.level;
    nextBlock = info.next;
    for(auto &block : info.b){
        if (block) {
            for(auto &cell : block->getInfo().cells){
                textDisplay[cell.x][cell.y] = block->getInfo().type;
            }
        }
    }
}

ostream &operator<<(ostream &out, const TextDisplay &td){
    cout << "Level:" << setw(7) << td.level << endl;
    cout << "Score:" << setw(7) << td.currentScore << endl;
    cout << "Hi Score:" << setw(4) << td.highScore << endl;
    
    for (int i = 0; i < width; i++){
        cout << "-";
    }
    cout << endl;
    for(int i = 0; i < height; i++){
        for(auto &column : td.textDisplay){
            out << column[17 - i];
        }
        out << endl;
    }
    
    for (int i = 0; i < width; i++){
        cout << "-";
    }
    cout << endl;
    
    cout << "Next:" << endl;
    char type = td.nextBlock->getInfo().type;
    switch (type) {
        case 'I':
            cout << "IIII" << endl;
            break;
            
        case 'J':
            cout << "J" << endl << "JJJ" << endl;
            break;
            
        case 'L':
            cout << "  L" << endl << "LLL" << endl;
            break;
            
        case 'Z':
            cout << "ZZ" << endl << " ZZ" << endl;
            break;
            
        case 'S':
            cout << " SS" << endl << "SS" << endl;
            break;
            
        case 'T':
            cout << "TTT" << endl << " T" << endl;
            break;
            
        case 'O':
            cout << "OO" << endl << "OO" << endl;
            break;
            
        default:
            break;
    }
    
    return out;
} 
