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
        if (this->ships[i].containsCoords(position))
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
            this->ships[i].setAlive(false);
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
        if (this->ships[i].containsCoords(position))
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


// Подсчет количества живых кораблей
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
