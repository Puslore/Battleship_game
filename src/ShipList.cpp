#include "ShipList.h"


ShipList::ShipList() {}


// Методы для управления кораблями
void ShipList::addShip(Ship ship)
{
    this->ships.push_back(ship);
}


void ShipList::removeShip(const Coords& position)
{
    for (int i = 0; i < this->ships.size(); i++)
    {
        // Создаем копию корабля для проверки без изменения оригинала
        Ship tempShip = this->ships[i];
        Coords tempCoords = position;
        if (tempShip.checkHit(tempCoords))
        {
            this->ships.erase(this->ships.begin() + i);
            return;
        }
    }
}


void ShipList::markAsDestroyed(Ship ship)
{
    for (int i = 0; i < this->ships.size(); i++)
    {
        if (this->ships[i].getType() == ship.getType())
        {
            this->ships[i].setAlive(false); // Временное решение - заменяем корабль
            return;
        }
    }
}


// Метод доступа к кораблям
std::vector<Ship> ShipList::getAllShips() const
{
    return this->ships;
}


// Методы для получения статусов
bool ShipList::isAnyShipAt(const Coords& position) const
{
    for (int i = 0; i < this->ships.size(); i++)
    {
        // Создаем копию корабля для проверки без изменения оригинала
        Ship tempShip = this->ships[i];
        Coords tempCoords = position;
        if (tempShip.checkHit(tempCoords))
        {
            return true;
        }
    }
    return false;
}


bool ShipList::isHit(const Coords& attackPosition) const
{
    return isAnyShipAt(attackPosition);
}


// Подсчет статистики
int ShipList::countAliveShips() const
{
    int count = 0;
    
    for (int i = 0; i < this->ships.size(); i++)
    {
        if (!this->ships[i].isDestroyed())
        {
            count++;
        }
    }
    
    return count;
}
