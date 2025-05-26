#include "../headers/Ship.h"


std::vector<Coords> Ship::getShipCoords() const
{
    return this->coords;
}


int Ship::getType() const
{
    return this->shipType;
}


bool Ship::checkHit(Coords& coords)
{
    for (int i = 0; i < this->coords.size(); i++)
    {
        if (this->coords[i] == coords)
        {
            // Пометка координаты как поврежденной при попадании
            this->coords[i].setDamaged(true);
            
            // Проверка, все ли части корабля повреждены
            bool allDamaged = true;
            for (int j = 0; j < this->coords.size(); j++)
            {
                if (!this->coords[j].isDamaged())
                {
                    allDamaged = false;
                    break;
                }
            }
            
            if (allDamaged)
            {
                this->isAlive = false;
            }
            
            return true;
        }
    }
    
    return false;
}


bool Ship::containsCoords(const Coords& coords) const
{
    for (int i = 0; i < this->coords.size(); i++)
    {
        if (this->coords[i] == coords)
        {
            return true;
        }
    }
    
    return false;
}


bool Ship::isDestroyed() const
{
    return !this->isAlive;
}


void Ship::setAliveStatus(bool status)
{
    this->isAlive = status;
}


// Конструктор для создания корабля
Ship::Ship(const int type, const std::vector<Coords>& coordinates, bool isAlive)
{
    this->shipType = type;
    this->coords = coordinates;
    this->isAlive = isAlive;
}


// Конструктор по умолчанию
Ship::Ship()
{
    this->shipType = 0;
    this->isAlive = false;
}
