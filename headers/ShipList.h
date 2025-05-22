#ifndef SHIPLIST_H
#define SHIPLIST_H

#include <string>
#include <vector>

#include "Ship.h"


class ShipList
{
    private:
        std::vector<Ship> ships;  // Коллекция кораблей
    
    public:
        // Конструкторы
        ShipList();
        
        // Методы для управления кораблями
        void addShip(Ship ship);
        void removeShip(const Coords& position);
        void markAsDestroyed(Ship ship);
        
        // Методы доступа к кораблям
        std::vector<Ship> getAllShips() const;
        
        // Методы для получения статусов
        bool isAnyShipAt(const Coords& position) const;
        bool isHit(const Coords& attackPosition) const;
        
        // Подсчет статистики
        int countAliveShips() const;
};


#endif
