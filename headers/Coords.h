#ifndef COORDS_H
#define COORDS_H

#include <string>
/*Реализация всех методов прямо в заголовочном файле
обусловлена тем, что изначально эта структура задумывалась
не такой большой. В конечном итоге не было выявлено
серьезных причин на создание отдельного cpp файла -
все методы в структуре не настолько большие для этого*/


struct Coords
{
    int x;              // Строка
    std::string y;      // Столбец
    bool damaged = false;
    
    // Конструкторы
    Coords()
    {
        this->x = 0;
        this->y = "А";
        this->damaged = false;
    }
    
    Coords(int x, const std::string& y)
    {
        this->x = x;
        this->y = y;
        this->damaged = false;
    }
    
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
    bool operator==(const Coords& other) const
    {
        return (this->x == other.x && this->y == other.y);
    }
};


#endif
