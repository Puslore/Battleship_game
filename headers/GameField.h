#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "ShipList.h"
// #include "Player.h"
#include <vector>
#include <string>


class GameField
{
    private:
        ShipList ShipList; // Список кораблей на поле
        std::string playerName; // Имя грока
        
    public:
        // Конструктор
        GameField(const std::string& playerName);
        
        // Методы для размещения кораблей
        void placeShip(const Ship& ship);
        bool canPlaceShip(const Ship& ship) const;
        
        // Методы для стрельбы
        bool makeShot(const Coords& coords);
        
        // Проверка состояния игры
        bool isGameOver() const;
        
        // Отображение поля
        void printGameField(bool hideShips) const;
        
        // Случайное размещение кораблей
        bool placeShipsRandomly();
};


#endif
