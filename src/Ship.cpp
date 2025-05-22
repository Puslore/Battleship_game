#include "Ship.h"


std::string Ship::getType() const
{
    return this->shipType;
}


bool Ship::checkHit(Coords& hitCoords)
{
    for (int i = 0; i < this->coords.size(); i++)
    {
        if (this->coords[i] == hitCoords)
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

bool Ship::isDestroyed() const
{
    return !this->isAlive;
}


void Ship::setAlive(bool alive)
{
    this->isAlive = alive;
}


// Конструктор для создания корабля
Ship::Ship(const std::string& type, const std::vector<Coords>& coordinates)
{
    this->shipType = type;
    this->coords = coordinates;
    this->isAlive = true;
}

// Конструктор по умолчанию
Ship::Ship()
{
    this->shipType = "Unknown";
    this->isAlive = false;
}
