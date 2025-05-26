#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "./ShipList.h"
#include "Cell.h"


class GameField
{
    private:
        ShipList shipList; // Список кораблей на поле
        std::string playerName; // Имя грока
        std::vector<Cell> cells; // Символы на игровом поле
        const int FIELD_SIZE = 10;
        const std::vector<std::string> COLUMNS = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
        const std::vector<int> ROWS = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        // Проверка на то, что координаты находятся рядом и
        // образуют сплошную линию
        bool areCoordinatesInLine(const std::vector<Coords>& coords) const;
        // Проверка окружных ячеек вокруг координаты
        bool checkNearCells(const std::vector<Coords>& coords) const;
        // Получение координат 8 окружных ячеек
        std::vector<Coords> getNearCoords(const Coords& coord) const;

    public:
        // Конструктор
        GameField(const std::string& playerName);

        // Получение имени игрока
        std::string getName() const;

        // Получение количества кораблей на поле
        int getShipsAmount(int type=0) const;
        
        // Методы для размещения кораблей
        bool placeShip(const Ship& ship);
        bool canPlaceShip(const Ship& ship) const;
        
        // Метод для стрельбы
        bool makeShot(const Coords& coords);
        
        // Отображение поля
        void printGameField(bool hideShips) const;
        
        // Случайное размещение кораблей для компьютераа
        void placeShipsRandomly();

         // Статус атакованности ячейки
        bool isAlreadyShot(const Coords& coords) const;
};


#endif
