#ifndef SHIP_H
#define SHIP_H

#include "Coords.h"
#include <string>
#include <vector>


class Ship
{
    private:
        // тип корабля, координаты и состояние
        std::string shipType;
        std::vector<Coords> coords;
        bool isAlive;
        
    public:
        // Конструкторы и методы для работы с кораблем
        std::string getType() const;
        bool checkHit(Coords& coords);  // Проверка попадания
        bool isDestroyed() const;     // Проверка, уничтожен ли корабль
};



#endif
    