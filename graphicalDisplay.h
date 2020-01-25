
#ifndef _GRAPHICAL_DISPLAY_HEADER_
#define _GRAPHICAL_DISPLAY_HEADER_

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include "observer.h"
#include "info.h"
#include "window.h"
#include "cell.h"
#include "board.h"
class Board;
class GraphicalDisplay: public Observer {
    Xwindow window;
    BoardInfo prevBoard;
    
    void fillCell(int x, int y, int cellSize, Colour colour);
public:
    GraphicalDisplay();
    void notify(Subject &whoNotified) override;
};

#endif
