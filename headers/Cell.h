#ifndef CELL_H
#define CELL_H

#include "./Coords.h"


struct Cell
{
    Coords coords;
    std::string symbol;

    Cell(Coords coords, std::string symbol)
    {
        this->coords = coords;
        this->symbol = symbol;
    }
};



#endif