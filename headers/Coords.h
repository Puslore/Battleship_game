#ifndef COORDS_H
#define COORDS_H

#include <string>


struct Coords
{
    int x;              // Строка
    std::string y;      // Столбец
    bool damaged = false;
    
    // Конструкторы
    Coords();
    Coords(int x, const std::string& y);
    
    // Методы для работы с повреждениями
    bool isDamaged() const
    {
        return this->damaged;
    }
    void setDamaged(bool value)
    {
        this->damaged = value;
    }
    
    // Перегрузка оператора сравнения для проверки совпадения координат
    bool Coords::operator==(const Coords& other) const
    {
        return (this->x == other.x && this->y == other.y);
    }
};


#endif
