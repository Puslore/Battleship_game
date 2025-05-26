#ifndef SHIP_H
#define SHIP_H

#include "./Coords.h"
#include <string>
#include <vector>


class Ship
{
    private:
        // тип корабля, координаты и состояние
        int shipType;
        std::vector<Coords> coords;
        bool isAlive = true;
        
    public:
        // Конструкторы и методы для работы с кораблем
        Ship();
        Ship(const int type, const std::vector<Coords>& coords, bool isAlive=true);
        int getType() const; // Получение типа корабля
        std::vector<Coords> getShipCoords() const; // Получение вектора координат корабля
        void setAliveStatus(bool status);  // Установка статуса жив/мертв у корабля
        bool checkHit(Coords& coords);  // Проверка попадания
        bool containsCoords(const Coords& coords) const;  // Проверка координат
        bool isDestroyed() const;  // Проверка, уничтожен ли корабль
};


#endif
    