#include "../headers/GameField.h"
#include <algorithm>
#include <iostream>


GameField::GameField(const std::string& playerName)
{
    this->playerName = playerName;
    
    // Инициализация поля пустыми символами
    for (int i = 0; i < this->FIELD_SIZE; i++)
    {
        for (int j = 0; j < this->FIELD_SIZE; j++)
        {
            Coords coords(this->ROWS[i], this->COLUMNS[j]);
            Cell symbol(coords, "~");
            this->cells.push_back(symbol);
        }
    }
}


std::string GameField::getName() const
{
    return this->playerName;
}


int GameField::getShipsAmount(int type) const
{
    return this->shipList.countAliveShips(type);
}


bool GameField::placeShip(const Ship& ship)
{
    if (this->canPlaceShip(ship))
    {
        this->shipList.addShip(ship);
        
        // Обновляем символы на поле для отображения корабля
        std::vector<Coords> shipCoords = ship.getShipCoords();
        for (int i = 0; i < shipCoords.size(); i++)
        {
            for (int j = 0; j < this->cells.size(); j++)
            {
                if (this->cells[j].coords == shipCoords[i])
                {
                    this->cells[j].symbol = "▢";
                    break;
                }
            }
        }

        return true;
    }

    else
    {
        return false;
    }
}


bool GameField::canPlaceShip(const Ship& ship) const
{
    std::vector<Coords> shipCoords = ship.getShipCoords();
    
    // Проверяем каждую координату корабля
    for (int i = 0; i < shipCoords.size(); i++)
    {
        // Проверяем, находится ли координата в пределах поля
        bool validCoord = false;
        for (int row = 0; row < this->ROWS.size(); row++)
        {
            for (int col = 0; col < this->COLUMNS.size(); col++)
            {
                if (shipCoords[i].x == this->ROWS[row] && shipCoords[i].y == this->COLUMNS[col])
                {
                    validCoord = true;
                    break;
                }
            }
            if (validCoord) break;
        }
        
        if (!validCoord)
        {
            return false;
        }
        
        // Проверяем, не занята ли позиция другим кораблем
        if (this->shipList.isAnyShipAt(shipCoords[i]))
        {
            return false;
        }
    }

    if (!areCoordinatesInLine(shipCoords))
    {
        return false;
    }
    
    if (!checkNearCells(shipCoords))
    {
        return false;
    }

    return true;
}


bool GameField::makeShot(const Coords& coords)
{
    // Проверка повторного выстрела
    for (int i = 0; i < this->cells.size(); i++)
    {
        if (this->cells[i].coords == coords)
        {
            if (this->cells[i].symbol == "X" || this->cells[i].symbol == "O")
            {
                std::cout << "По этой клетке уже стреляли!" << std::endl;
                return false;
            }
            break;
        }
    }

    bool hit = this->shipList.isHit(coords);
    
    if (hit)
    {
        // Обновление символа на поле
        for (int i = 0; i < this->cells.size(); i++)
        {
            if (this->cells[i].coords == coords)
            {
                this->cells[i].symbol = "X";
                break;
            }
        }
        std::cout << "ПОПАДАНИЕ!" << std::endl;
        return true;
    }else
    {
        for (int i = 0; i < this->cells.size(); i++)
        {
            if (this->cells[i].coords == coords)
            {
                this->cells[i].symbol = "O";
                break;
            }
        }
        std::cout << "МИМО!" << std::endl;
        return false;
    }
}


bool GameField::isAlreadyShot(const Coords& coords) const
{
    for (int i = 0; i < this->cells.size(); i++)
    {
        if (this->cells[i].coords == coords && 
            (this->cells[i].symbol == "X" || this->cells[i].symbol == "O"))
        {
            return true;
        }
    }
    return false;
}


void GameField::printGameField(bool hideShips) const
{
    std::cout << "Поле игрока: " << this->playerName << std::endl;
    std::cout << "  ";
    
    // Печатаем заголовок с буквами столбцов
    for (int i = 0; i < this->COLUMNS.size(); i++)
    {
        std::cout << this->COLUMNS[i] << " ";
    }
    std::cout << std::endl;
    
    // Печатаем строки поля
    for (int row = 0; row < this->ROWS.size(); row++)
    {
        std::cout << this->ROWS[row];
        if (this->ROWS[row] < 10)
        {
            std::cout << " ";
        }
        
        for (int col = 0; col < this->COLUMNS.size(); col++)
        {
            // Находим символ для данной позиции
            std::string displaySymbol = "~";
            for (int i = 0; i < this->cells.size(); i++)
            {
                if (this->cells[i].coords.x == this->ROWS[row] && 
                    this->cells[i].coords.y == this->COLUMNS[col])
                {
                    displaySymbol = this->cells[i].symbol;
                    break;
                }
            }
            
            // Скрываем корабли если нужно
            if (hideShips && displaySymbol == "S")
            {
                displaySymbol = "~";
            }
            
            std::cout << displaySymbol << " ";
        }
        std::cout << std::endl;
    }
}


void GameField::placeShipsRandomly()
{    
    // Количество кораблей каждого типа
    std::vector<int> shipTypes = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
    
    for (int i = 0; i < shipTypes.size(); i++)
    {
        int shipType = shipTypes[i];
        Ship newShip;
        bool placed = false;
        int attempts = 0;
        const int MAX_ATTEMPTS = 1000; // Предотвращение бесконечного цикла
        
        while (!placed && attempts < MAX_ATTEMPTS)
        {
            attempts++;
            
            // Случайная начальная позиция
            int startX = this->ROWS[rand() % this->ROWS.size()];
            std::string startY = this->COLUMNS[rand() % this->COLUMNS.size()];
            
            // Случайная ориентация
            bool isHorizontal = (rand() % 2 == 0);
            
            std::vector<Coords> shipCoords;
            bool validPlacement = true;
            
            for (int j = 0; j < shipType; j++)
            {
                int currentX = startX;
                std::string currentY = startY;
                
                if (isHorizontal)
                {
                    int startColIndex = -1;
                    for (int k = 0; k < this->COLUMNS.size(); k++)
                    {
                        if (this->COLUMNS[k] == startY)
                        {
                            startColIndex = k;
                            break;
                        }
                    }
                    
                    int newColIndex = startColIndex + j;
                    if (newColIndex >= this->COLUMNS.size())
                    {
                        validPlacement = false;
                        break;
                    }
                    currentY = this->COLUMNS[newColIndex];
                }else
                {
                    int startRowIndex = -1;
                    for (int k = 0; k < this->ROWS.size(); k++)
                    {
                        if (this->ROWS[k] == startX)
                        {
                            startRowIndex = k;
                            break;
                        }
                    }
                    
                    int newRowIndex = startRowIndex + j;
                    if (newRowIndex >= this->ROWS.size())
                    {
                        validPlacement = false;
                        break;
                    }
                    currentX = this->ROWS[newRowIndex];
                }
                
                shipCoords.push_back(Coords(currentX, currentY));
            }
            
            // Проверка на правильность размещения
            if (validPlacement)
            {
                newShip = Ship(shipType, shipCoords);
                if (this->canPlaceShip(newShip))
                {
                    this->placeShip(newShip);
                    placed = true;
                    
                    // Отладка
                    std::cout << "Размещен " << shipType << "-палубный корабль: ";
                    for (int k = 0; k < shipCoords.size(); k++)
                    {
                        std::cout << shipCoords[k].y << shipCoords[k].x;
                        if (k < shipCoords.size() - 1) std::cout << ", ";
                    }
                    std::cout << std::endl;
                }
            }
        }
        
        if (!placed)
        {
            std::cout << "Ошибка: Не удалось разместить " << shipType << "-палубный корабль за " 
                      << MAX_ATTEMPTS << " попыток!" << std::endl;
        }
    }
    
    std::cout << "Автоматическое размещение кораблей завершено!" << std::endl;
    std::cout << "Всего размещено кораблей: " << this->getShipsAmount() << std::endl;
}



bool GameField::areCoordinatesInLine(const std::vector<Coords>& coords) const
{
    if (coords.size() <= 1) return true;

    // Проверка, что координаты либо все в одной строке, либо все в одном столбце
    bool sameRow = true, sameCol = true;
    for (int i = 1; i < coords.size(); i++)
    {
        if (coords[i].x != coords[0].x) sameRow = false;
        if (coords[i].y != coords[0].y) sameCol = false;
    }

    if (!sameRow && !sameCol) return false;

    // Проверяем непрерывность координат
    std::vector<int> indices;
    
    if (sameRow)
    {
        // Корабль горизонтальный - проверяем по столбцам
        for (int i = 0; i < coords.size(); i++)
        {
            for (int j = 0; j < this->COLUMNS.size(); j++)
            {
                if (coords[i].y == this->COLUMNS[j])
                {
                    indices.push_back(j);
                    break;
                }
            }
        }
    }else
    {
        // Корабль вертикальный - проверяем по строкам
        for (int i = 0; i < coords.size(); i++)
        {
            for (int j = 0; j < this->ROWS.size(); j++)
            {
                if (coords[i].x == this->ROWS[j])
                {
                    indices.push_back(j);
                    break;
                }
            }
        }
    }

    // Сортируем индексы и проверяем непрерывность
    for (int i = 0; i < indices.size() - 1; i++)
    {
        for (int j = 0; j < indices.size() - 1 - i; j++)
        {
            if (indices[j] > indices[j + 1])
            {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < indices.size() - 1; i++)
    {
        if (indices[i + 1] - indices[i] != 1)
        {
            return false;
        }
    }

    return true;
}


std::vector<Coords> GameField::getNearCoords(const Coords& coord) const
{
    std::vector<Coords> surrounding;
    
    // 8 направлений: верх, низ, лево, право и 4 диагонали
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0) continue; // Пропускаем саму клетку
            
            int newX = coord.x + dx;
            
            // Проверяем, что новая строка существует
            bool validRow = false;
            for (int i = 0; i < this->ROWS.size(); i++)
            {
                if (this->ROWS[i] == newX)
                {
                    validRow = true;
                    break;
                }
            }
            if (!validRow) continue;
            
            // Находим индекс текущего столбца
            int currentColIndex = -1;
            for (int i = 0; i < this->COLUMNS.size(); i++)
            {
                if (this->COLUMNS[i] == coord.y)
                {
                    currentColIndex = i;
                    break;
                }
            }
            if (currentColIndex == -1) continue;
            
            // Вычисляем новый индекс столбца
            int newColIndex = currentColIndex + dy;
            if (newColIndex < 0 || newColIndex >= this->COLUMNS.size()) continue;
            
            surrounding.push_back(Coords(newX, this->COLUMNS[newColIndex]));
        }
    }
    
    return surrounding;
}


bool GameField::checkNearCells(const std::vector<Coords>& coords) const
{
    for (int i = 0; i < coords.size(); i++)
    {
        std::vector<Coords> surrounding = getNearCoords(coords[i]);
        
        for (int j = 0; j < surrounding.size(); j++)
        {
            bool isPartOfCurrentShip = false;
            for (int k = 0; k < coords.size(); k++)
            {
                if (surrounding[j].x == coords[k].x && surrounding[j].y == coords[k].y)
                {
                    isPartOfCurrentShip = true;
                    break;
                }
            }
            
            if (!isPartOfCurrentShip && this->shipList.isAnyShipAt(surrounding[j]))
            {
                return false;
            }
        }
    }
    return true;
}
