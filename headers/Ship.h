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
        bool isAlive = true;
        
    public:
        // Конструкторы и методы для работы с кораблем
        Ship();
        Ship(const std::string& type, const std::vector<Coords>& coordinates);
        std::string getType() const;
        void setAlive(bool alive); // Установка статуса жив/мертв у корабля
        bool checkHit(Coords& coords);  // Проверка попадания
        bool containsCoords(const Coords& coords) const; // Проверка координат
        bool isDestroyed() const;     // Проверка, уничтожен ли корабль
};



#endif
    