#include "../headers/ShipList.h"
#include <iostream>


ShipList::ShipList() {}


// Методы для управления кораблями
void ShipList::addShip(Ship ship)
{
    this->ships.push_back(ship);
}


void ShipList::removeShip(Ship ship)
{
    for (int i = 0; i < this->ships.size(); i++)
    {
        // Корабли сравниваются по типу(std::string)
        // и по координатам(std::vector<Coords>)
        std::vector<Coords> currentShipCoords = this->ships[i].getShipCoords();
        std::vector<Coords> targetShipCoords = ship.getShipCoords();
        
        if (currentShipCoords.size() == targetShipCoords.size())
        {
            bool coordsMatch = true;
            for (int j = 0; j < currentShipCoords.size(); j++)
            {
                bool found = false;
                for (int k = 0; k < targetShipCoords.size(); k++)
                {
                    if (currentShipCoords[j] == targetShipCoords[k])
                    {
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    coordsMatch = false;
                    break;
                }
            }
            
            if (coordsMatch)
            {
                this->ships.erase(this->ships.begin() + i);
                return;
            }
        }
    }
}


void ShipList::markAsDestroyed(Ship ship)
{
    for (int i = 0; i < this->ships.size(); i++)
    {
        if (this->ships[i].getType() == ship.getType())
        {
            this->ships[i].setAliveStatus(false);
            return;
        }
    }
}


// Метод доступа к вектору кораблей
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


bool ShipList::isHit(const Coords& attackPosition)
{
    for (int i = 0; i < this->ships.size(); i++)
    {
        if (this->ships[i].containsCoords(attackPosition))
        {
            Coords attackCoords = attackPosition;
            bool hit = this->ships[i].checkHit(attackCoords);
            
            if (hit && this->ships[i].isDestroyed())
            {
                std::cout << "КОРАБЛЬ ПОТОПЛЕН!" << std::endl;
            }
            
            return hit;
        }
    }
    return false;
}



// Подсчет статистики
int ShipList::countAliveShips(int type) const
{
    int count = 0;
    
    if (type == 0)
    {   for (int i = 0; i < this->ships.size(); i++)
        {
            if (!this->ships[i].isDestroyed())
            {
                count++;
            }
        }
    }

    else
    {
        for (int i = 0; i < this->ships.size(); i++)
        {
            if (!this->ships[i].isDestroyed() && this->ships[i].getType() == type)
            {
                count++;
            }
        }
    }

    return count;
}
