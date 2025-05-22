// Coords.h
#ifndef COORDS_H
#define COORDS_h

#include <string>


struct Coords
{
    int x;
    std::string y;
    
    // Конструктор структуры, хранящей координаты корабля
    Coords(int x, std::string y) : x(x), y(y) {}
    
    // Операторы сравнения
    bool operator==(const Coords& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Coords& other) const {
        return !(*this == other);
    }
};


#endif
