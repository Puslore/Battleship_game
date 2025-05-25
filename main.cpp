#include "./headers/GameField.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int main()
{
    string name1, name2;
    cout << "Игра 'Морской бой' ";
    cout << "Введите имя первого игрока:";
    cin >> name1;
    cout << "Введите имя второго игрока,\nлибо нажмите enter чтобы играть против компьютера:";
    cin >> name2;
    if (name2 == "")
    {
        name2 == "COMP";
    }

    GameField player1(name1);
    GameField player2(name2);
    
    srand(time(nullptr)); // Порядок игрока зависит от случайного числа(четный, нечетный)
    int queue = (rand() % 2) + 1;
    int cnt = 1;

    if (queue == 1)
    {
        cout << "Первым ходит игрок 1 - " << player1.getName();
        cout << player1.getName() << ", расставьте корабли!";
        while (player1.getShipsAmount() < 10)
        {
            cout << "Введите тип корабля(1 - однопалубный и т.д.)";
            int shipType;
            cin >> shipType;
            switch (shipType)
            {
                case 1:
                    if (player1.getShipsAmount(1) < 4)
                    {
                        std::string inp;
                        cout << "Введите координаты корабля(А1, Д8 и т.д.)";
                        cin >> inp;
                        if (inp.size() < 2 || !std::isdigit(inp[1]))
                        {
                            cout << "Неправильный формат ввода! Введите А1, Д8 и т.д.";
                            continue;
                        }
                        std::string letter = inp.substr(0, 1);  // Отделение буквы от цифры
                        int x = std::stoi(inp.substr(1));
                        
                        player1.placeShip(Ship(1, std::vector<Coords>{Coords(x, letter)}));
                        cout << "Торпедоносец " << inp << " добавлен\n ";
                        continue;
                    }
                    
                    else
                    {
                        cout << "У вас уже есть 4 торпедных корабля, выберите другой!";
                        continue;
                    }
                
                case 2:
                    if (player1.getShipsAmount(2) < 3)
                    {
                        std::vector<Coords> coords = {};
                        while (coords.size() < 2)
                        {
                            std::string inp;
                            cout << "Введите координаты " << (coords.size() + 1) << "-й палубы корабля (А1, Д8 и т.д.): ";
                            cin >> inp;
                            
                            if (inp.size() < 2 || !std::isdigit(inp[1]))
                            {
                                cout << "Неправильный формат ввода! Введите А1, Д8 и т.д." << endl;
                                continue;
                            }
                            
                            std::string letter = inp.substr(0, 1);
                            int x = std::stoi(inp.substr(1));
                            
                            Coords newCoord(x, letter);
                            
                            // Проверка на повторение координаты
                            bool duplicate = false;
                            for (int i = 0; i < coords.size(); i++)
                            {
                                if (coords[i].x == newCoord.x && coords[i].y == newCoord.y)
                                {
                                    cout << "Эта координата уже введена! Введите другую." << endl;
                                    duplicate = true;
                                    break;
                                }
                            }
                            
                            if (duplicate)
                            {
                                continue;
                            }
                            
                            coords.push_back(newCoord);
                            
                            cout << "Координата " << inp << " добавлена. ";
                            if (coords.size() < 2)
                            {
                                cout << "Введите координату следующей палубы." << endl;
                            }
                        }
                        
                        // Попытка разместить корабль
                        if (player1.placeShip(Ship(2, coords)))
                        {
                            cout << "Эсминец успешно размещен!" << endl;
                        }
                        else
                        {
                            cout << "Ошибка размещения корабля! " << endl;
                            cout << "Возможные причины:" << endl;
                            cout << "- Координаты не образуют прямую линию" << endl;
                            cout << "- Корабль касается других кораблей" << endl;
                            cout << "- Координаты выходят за границы поля" << endl;
                            cout << "Попробуйте снова." << endl;
                        }
                    }
                    else
                    {
                        cout << "У вас уже есть 3 эсминца, выберите другой!" << endl;
                        continue;
                    }
                    break;


                case 3:
                    if (player1.getShipsAmount(3) < 2)
                    {
                        std::vector<Coords> coords = {};
                        while (coords.size() < 3)
                        {
                            std::string inp;
                            cout << "Введите координаты " << (coords.size() + 1) << "-й палубы корабля (А1, Д8 и т.д.): ";
                            cin >> inp;
                            
                            if (inp.size() < 2 || !std::isdigit(inp[1]))
                            {
                                cout << "Неправильный формат ввода! Введите А1, Д8 и т.д." << endl;
                                continue;
                            }
                            
                            std::string letter = inp.substr(0, 1);
                            int x = std::stoi(inp.substr(1));
                            
                            // Создаем координату
                            Coords newCoord(x, letter);
                            
                            // Проверяем, не повторяется ли координата
                            bool duplicate = false;
                            for (int i = 0; i < coords.size(); i++)
                            {
                                if (coords[i].x == newCoord.x && coords[i].y == newCoord.y)
                                {
                                    cout << "Эта координата уже введена! Введите другую." << endl;
                                    duplicate = true;
                                    break;
                                }
                            }
                            
                            if (duplicate) continue;
                            
                            // Добавляем координату
                            coords.push_back(newCoord);
                            
                            cout << "Координата " << inp << " добавлена. ";
                            if (coords.size() < 3)
                            {
                                cout << "Введите координату следующей палубы." << endl;
                            }
                        }
                        
                        // Создаем трехпалубный корабль
                        Ship ship(3, coords);
                        
                        // Пытаемся разместить корабль
                        if (player1.placeShip(ship))
                        {
                            cout << "Крейсер успешно размещен!" << endl;
                        }
                        else
                        {
                            cout << "Ошибка размещения корабля! " << endl;
                            cout << "Возможные причины:" << endl;
                            cout << "- Координаты не образуют прямую линию" << endl;
                            cout << "- Корабль касается других кораблей" << endl;
                            cout << "- Координаты выходят за границы поля" << endl;
                            cout << "Попробуйте снова." << endl;
                        }
                    }
                    else
                    {
                        cout << "У вас уже есть 2 крейсера, выберите другой!" << endl;
                        continue;
                    }
                    break;
                    
                case 4:
                    if (player1.getShipsAmount(4) < 1)
                    {
                        std::vector<Coords> coords = {};
                        while (coords.size() < 4)
                        {
                            std::string inp;
                            cout << "Введите координаты " << (coords.size() + 1) << "-й палубы корабля (А1, Д8 и т.д.): ";
                            cin >> inp;
                            
                            if (inp.size() < 2 || !std::isdigit(inp[1]))
                            {
                                cout << "Неправильный формат ввода! Введите А1, Д8 и т.д." << endl;
                                continue;
                            }
                            
                            std::string letter = inp.substr(0, 1);
                            int x = std::stoi(inp.substr(1));
                            
                            // Создаем координату
                            Coords newCoord(x, letter);
                            
                            // Проверяем, не повторяется ли координата
                            bool duplicate = false;
                            for (int i = 0; i < coords.size(); i++)
                            {
                                if (coords[i].x == newCoord.x && coords[i].y == newCoord.y)
                                {
                                    cout << "Эта координата уже введена! Введите другую." << endl;
                                    duplicate = true;
                                    break;
                                }
                            }
                            
                            if (duplicate) continue;
                            
                            // Добавляем координату
                            coords.push_back(newCoord);
                            
                            cout << "Координата " << inp << " добавлена. ";
                            if (coords.size() < 4)
                            {
                                cout << "Введите координату следующей палубы." << endl;
                            }
                        }
                        
                        // Создаем четырехпалубный корабль
                        Ship ship(4, coords);
                        
                        // Пытаемся разместить корабль
                        if (player1.placeShip(ship))
                        {
                            cout << "Линкор успешно размещен!" << endl;
                        }
                        else
                        {
                            cout << "Ошибка размещения корабля! " << endl;
                            cout << "Возможные причины:" << endl;
                            cout << "- Координаты не образуют прямую линию" << endl;
                            cout << "- Корабль касается других кораблей" << endl;
                            cout << "- Координаты выходят за границы поля" << endl;
                            cout << "Попробуйте снова." << endl;
                        }
                    }
                    else
                    {
                        cout << "У вас уже есть 1 линкор, выберите другой!" << endl;
                        continue;
                    }
                    break;
                    
                
                default:
                    continue;
            }
            player1.printGameField(false);
        }

    }
    else
    {
        cout << "Первым ходит игрок 2 - " << player2.getName();
        cout << player1.getName() << ", расставьте корабли!";
        while (player1.getShipsAmount() < 10)
        {
            cout << "Введите тип корабля(1 - однопалубный и т.д.)";
            int shipType;
            cin >> shipType;
            if (shipType > 4 || shipType < 1)
            {
                cout << "Неправильный ввод! Введите 1, 2, 3 или 4";
                continue;
            }
            
            switch (shipType)
            {
                case 1:
                    if (player1.getShipsAmount(1) < 4)
                    {

                    }
                    break;
                
                case 2:
                    /* code */
                    break;

                case 3:
                    /* code */
                    break;

                case 4:
                    /* code */
                    break;
            }
            player1.printGameField(false);
        }

    }
    
    
    return 0;
}
