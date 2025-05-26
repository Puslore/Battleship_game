#ifndef SHIPLIST_H
#define SHIPLIST_H

#include <string>
#include <vector>

#include "./Ship.h"


class ShipList
{
    private:
        std::vector<Ship> ships;  // Вектор кораблей
    
    public:
        ShipList();
        
        // Методы для управления кораблями
        void addShip(Ship ship);
        // void removeShip(const Coords& coords);
        void removeShip(Ship ship);
        void markAsDestroyed(Ship ship);
        
        // Метод доступа к вектору кораблей
        std::vector<Ship> getAllShips() const;
        
        // Методы для получения статусов
        bool isAnyShipAt(const Coords& coords) const;
        bool isHit(const Coords& coords);
        
        // Подсчет статистики
        int countAliveShips(int type=0) const;
};


#endif
