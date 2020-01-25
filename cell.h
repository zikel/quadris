//
//  cell.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#ifndef _CELL_HEADER_
#define _CELL_HEADER_

#include "enum.h"

struct Cell {
    int x;
    int y;
    bool isFilled;
    Colour colour;
    
    Cell(int x, int y, bool isFilled, Colour colour):
    x{x}, y{y}, isFilled{isFilled}, colour{colour}{}

    bool operator==(const Cell &rhs){
        return (x == rhs.x && y == rhs.y &&
                isFilled == rhs.isFilled &&
                colour == rhs.colour);
    }
};

#endif
