#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "ShipList.h"


class GameField
{
    private:
        ShipList ShipList; // Список кораблей на поле
        std::string playerName; // Имя грока
        static const int FIELD_SIZE = 10;
        const std::vector<std::string> COLUMNS = {"А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "К"};
        const std::vector<int> ROWS = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    public:
        // Конструктор
        GameField(const std::string& playerName);
        
        // Методы для размещения кораблей
        void placeShip(const Ship& ship);
        bool canPlaceShip(const Ship& ship) const;
        
        // Метод для стрельбы
        bool cumShot(const Coords& coords);
        
        // Проверка состояния игры
        bool isGameOver() const;
        
        // Отображение поля
        void printGameField(bool hideShips) const;
        
        // Случайное размещение кораблей
        bool placeShipsRandomly();
};


#endif
