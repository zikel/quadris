//
//  main.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//
#include "board.h"
#include "enum.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[]) {
    int lvl = 0;
    int seed = 1;
    bool isText = false;
    string myfile = "sequence.txt";
    
    vector<string> left {"lef", "left"};
    vector<string> right {"ri", "rig", "righ", "right"};
    vector<string> down {"do", "dow", "down"};
    vector<string> clock {"cl", "clo", "cloc", "clock", "clockw",
        "clockwi", "clockwis", "clockwise"};
    vector<string> counter {"co", "cou", "coun", "count", "counte",
        "counter", "counterc", "countercl",
        "counterclo", "countercloc", "counterclock",
        "counterclockw", "counterclockwi",
        "counterclockwis", "counterclockwise"};
    vector<string> drop {"dr", "dro", "drop"};
    vector<string> lvlup {"levelu", "levelup", "lvlu",
        "lvl+", "level+"};
    vector<string> lvldo {"leveld", "leveldo", "leveldow",
        "leveldown", "level-", "lvld", "lvl-"};
    vector<string> noran {"n", "no", "nor", "nora", "norand",
        "norando", "norandom"};
    vector<string> rand {"ra", "rand", "rando", "random"};
    vector<string> seq {"s", "se", "seq", "sequ", "seque",
        "sequen", "sequenc", "sequence"};
    vector<string> restart {"re", "res", "rest",
        "resta", "restar", "restart"};
    vector<string> hint {"h", "hi", "hin", "hint", "?"};
    
    for(int i = 0; i < argc; i++){
        if (string(argv[i]) == "-scriptfile") {
            myfile = argv[i + 1];
        }
        if (string(argv[i]) == "-text"){
            isText = true;
        }
        if (string(argv[i]) == "-startlevel") {
            istringstream ss{argv[i+1]};
            int l;
            if (ss >> l && 0 <= l && 4 >= l) {
                lvl = l;
                ++i;
            } else {
                throw invalid_argument("Startlevel expected an integer (0 - 4)");
            }
        }
        
        if (string(argv[i]) == "-seed") {
            istringstream ss{argv[i+1]};
            if (ss >> seed && 1 <= seed) {
                ++i;
            } else {
                throw invalid_argument("Seed expected a positive integer");
            }
        }
    }
    
    string cmd;
    Board b{myfile, isText, seed};
    b.init(lvl);
    ifstream commandSeq;
    bool isGameover = false;
    
    try {
        
        while (true) {
            if (isGameover){
                cout << "Y or N for new game" << endl;
                if (cin >> cmd && cmd == "Y"){
                    b.init();
                    isGameover = false;
                } else {
                    return 0;
                }
            }
            if(!(commandSeq >> cmd)){
                cin >> cmd;
                if(commandSeq.is_open()) commandSeq.close();
            }
            istringstream iss{cmd};
            int multiples=1;
            iss >> multiples >> cmd;
            if(iss.fail()) multiples = 1;
            
            b.removeHint();
            
            if (find(left.begin(), left.end(), cmd) != left.end()) {
                b.move(MoveDirection::Left, multiples);
            } else if (find(right.begin(), right.end(), cmd) != right.end()) {
                b.move(MoveDirection::Right, multiples);
            } else if (find(down.begin(), down.end(), cmd) != down.end()) {
                b.move(MoveDirection::Down, multiples);
            } else if (find(clock.begin(), clock.end(), cmd) != clock.end()) {
                b.rotate(RotateDirection::Clockwise, multiples);
            } else if (find(counter.begin(), counter.end(), cmd) != counter.end()) {
                b.rotate(RotateDirection::CounterClockwise, multiples);
            } else if (find(drop.begin(), drop.end(), cmd) != drop.end()) {
                b.drop(multiples);
            } else if (find(lvlup.begin(), lvlup.end(), cmd) != lvlup.end()) {
                for (int i = 0; i < multiples; i++){
                    b.levelUp();
                }
            } else if (find(lvldo.begin(), lvldo.end(), cmd) != lvldo.end()) {
                for (int i = 0; i < multiples; i++){
                    b.levelDown();
                }
            } else if (find(rand.begin(), rand.end(), cmd) != rand.end()) {
                if (b.getLevel() == 3) {
                    b.changeLevel(3, "");
                } else if (b.getLevel() == 4) {
                    b.changeLevel(4, "");
                }
            } else if (find(noran.begin(), noran.end(), cmd) != noran.end()) {
                string file;
                if (cin >> file) {
                    if (b.getLevel() == 3) {
                        b.changeLevel(3, file);
                    } else if (b.getLevel() == 4) {
                        b.changeLevel(4, file);
                    } else {
                        cout <<
                        "norandom command only valid in Level 3 & 4."
                        << endl;
                    }
                } else {
                    cout << "Invalid file name." << endl;
                }
            } else if (find(seq.begin(), seq.end(), cmd) != seq.end()) {
                string file;
                if (cin >> file) {
                    commandSeq.open(file, std::ifstream::in);
                    if (commandSeq.peek() != EOF) continue;
                } else {
                    cout << "Invalid file name." << endl;
                }
            } else if (cmd == "I") {
                b.changeBlock('I');
            } else if (cmd == "J") {
                b.changeBlock('J');
            } else if (cmd == "T") {
                b.changeBlock('T');
            } else if (cmd == "S") {
                b.changeBlock('S');
            } else if (cmd == "Z") {
                b.changeBlock('Z');
            } else if (cmd == "O") {
                b.changeBlock('O');
            } else if (cmd == "L") {
                b.changeBlock('L');
            } else if (find(hint.begin(), hint.end(), cmd) != hint.end()) {
                b.getHint();
                continue;
            } else if (find(restart.begin(), restart.end(), cmd) != restart.end()) {
                b.init(lvl);
            } else if (cmd == "bonusOn") {
                b.setBonus(true);
            } else if (cmd == "bonusOff") {
                b.setBonus(false);
            }
            if (b.isOver()){
                cout << "Gameover" << endl;
                isGameover = true;
            }
        }
    }
    catch (invalid_argument &ia) {
        cout << ia.what() << endl;
    }
    
}

