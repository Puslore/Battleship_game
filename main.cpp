#include "./headers/GameField.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Функция ручного размещения кораблей
void manualShipPlacement(GameField& player)
{
    player.printGameField(false);
    cout << player.getName() << ", расставьте корабли!" << endl;
    
    while (player.getShipsAmount() < 10)
    {
        cout << "Введите тип корабля(1 - однопалубный и т.д.): ";
        int shipType;
        
        if (!(cin >> shipType))
        {
            cout << "Ошибка чтения ввода! Введите число от 1 до 4." << endl;
            cin.clear();                    // Очистка флагов ошибки
            cin.ignore(10000, '\n');        // Очистка буфера ввода
            continue;
        }
        
        if (shipType > 4 || shipType < 1)
        {
            cout << "Неправильный ввод! Введите 1, 2, 3 или 4" << endl;
            continue;
        }
        
        switch (shipType)
        {
            case 1:
            if (player.getShipsAmount(1) < 4)
            {
                std::string inp;
                cout << "Введите координаты корабля(A1, D8 и т.д.): ";
                cin >> inp;
                // Улучшенная проверка формата
                if (inp.size() < 2 || inp.size() > 3 ||
                    !std::isdigit(inp[1]) ||
                    (inp.size() == 3 && !std::isdigit(inp[2])))
                {
                    cout << "Неправильный формат ввода! Введите A1, D8 и т.д." << endl;
                    continue;
                }
                
                std::string letter = inp.substr(0, 1);
                int x = std::stoi(inp.substr(1));
                // Добавить проверку диапазона
                if (x < 1 || x > 10)
                {
                    cout << "Номер строки должен быть от 1 до 10!" << endl;
                    continue;
                }
                
                if (player.placeShip(Ship(1, std::vector<Coords>{Coords(x, letter)})))
                {
                    player.printGameField(false);
                    cout << "Торпедоносец " << inp << " добавлен" << endl;
                }
                else
                {
                    cout << "Ошибка размещения корабля! Попробуйте снова." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            else
            {
                cout << "У вас уже есть 4 торпедоносца, выберите другой!" << endl;
            }
            break;
            
            case 2:
            if (player.getShipsAmount(2) < 3)
            {
                std::vector<Coords> coords = {};
                while (coords.size() < 2)
                {
                    std::string inp;
                    cout << "Введите координаты " << (coords.size() + 1) << "-й палубы корабля (A1, D8 и т.д.): ";
                    cin >> inp;
                    if (inp.size() < 2 || !std::isdigit(inp[1]))
                    {
                        cout << "Неправильный формат ввода! Введите A1, D8 и т.д." << endl;
                        continue;
                    }
                    
                    std::string letter = inp.substr(0, 1);
                    int x = std::stoi(inp.substr(1));
                    Coords newCoord(x, letter);
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
                    
                    coords.push_back(newCoord);
                    cout << "Координата " << inp << " добавлена. ";
                    if (coords.size() < 2)
                    {
                        cout << "Введите координату следующей палубы." << endl;
                    }
                }
                
                if (player.placeShip(Ship(2, coords)))
                {
                    player.printGameField(false);
                    cout << "Эсминец успешно размещен!" << endl;
                }
                else
                {
                    cout << "Ошибка размещения корабля! Попробуйте снова." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            else
            {
                cout << "У вас уже есть 3 эсминца, выберите другой!" << endl;
            }
            break;
            
            case 3:
            if (player.getShipsAmount(3) < 2)
            {
                std::vector<Coords> coords = {};
                while (coords.size() < 3)
                {
                    std::string inp;
                    cout << "Введите координаты " << (coords.size() + 1) << "-й палубы корабля (A1, D8 и т.д.): ";
                    cin >> inp;
                    if (inp.size() < 2 || !std::isdigit(inp[1]))
                    {
                        cout << "Неправильный формат ввода! Введите A1, D8 и т.д." << endl;
                        continue;
                    }
                    
                    std::string letter = inp.substr(0, 1);
                    int x = std::stoi(inp.substr(1));
                    Coords newCoord(x, letter);
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
                    
                    coords.push_back(newCoord);
                    cout << "Координата " << inp << " добавлена. ";
                    if (coords.size() < 3)
                    {
                        cout << "Введите координату следующей палубы." << endl;
                    }
                }
                
                if (player.placeShip(Ship(3, coords)))
                {
                    player.printGameField(false);
                    cout << "Крейсер успешно размещен!" << endl;
                }
                else
                {
                    cout << "Ошибка размещения корабля! Попробуйте снова." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            else
            {
                cout << "У вас уже есть 2 крейсера, выберите другой!" << endl;
            }
            break;
            
            case 4:
            if (player.getShipsAmount(4) < 1)
            {
                std::vector<Coords> coords = {};
                while (coords.size() < 4)
                {
                    std::string inp;
                    cout << "Введите координаты " << (coords.size() + 1) << "-й палубы корабля (A1, D8 и т.д.): ";
                    cin >> inp;
                    if (inp.size() < 2 || !std::isdigit(inp[1]))
                    {
                        cout << "Неправильный формат ввода! Введите A1, D8 и т.д." << endl;
                        continue;
                    }
                    
                    std::string letter = inp.substr(0, 1);
                    int x = std::stoi(inp.substr(1));
                    Coords newCoord(x, letter);
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
                    
                    coords.push_back(newCoord);
                    cout << "Координата " << inp << " добавлена. ";
                    if (coords.size() < 4)
                    {
                        cout << "Введите координату следующей палубы." << endl;
                    }
                }
                
                if (player.placeShip(Ship(4, coords)))
                {
                    player.printGameField(false);
                    cout << "Линкор успешно размещен!" << endl;
                }
                else
                {
                    cout << "Ошибка размещения корабля! Попробуйте снова." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            else
            {
                cout << "У вас уже есть 1 линкор, выберите другой!" << endl;
            }
            break;
            
            default:
            cout << "Неверный тип корабля!" << endl;
            break;
        }
    }
    
    cout << "Размещение кораблей завершено!" << endl;
    player.printGameField(false);
}

// Для компьютера
void computerShipPlacement(GameField& player)
{
    cout << "Компьютер " << player.getName() << " размещает корабли..." << endl;
    player.placeShipsRandomly();
    cout << "Компьютер " << player.getName() << " завершил размещение кораблей!" << endl;
    
    // Показать поле компьютера (чтобы проверить все ли правильно расставлено)
    cout << "Поле компьютера (для отладки):" << endl;
    player.printGameField(false);
}


void startBattle(GameField& player1, GameField& player2, bool isPlayer1Computer, bool isPlayer2Computer)
{
    cout << "\n===== НАЧАЛО БОЕВОЙ ФАЗЫ =====" << endl;
    
    GameField* currentPlayer = &player1;
    GameField* opponent = &player2;
    bool isCurrentPlayerComputer = isPlayer1Computer;
    
    while (player1.getShipsAmount() > 0 && player2.getShipsAmount() > 0)
    {
        // Отображение полей
        cout << "\n--- Ход игрока: " << currentPlayer->getName() << " ---" << endl;
        cout << "Ваше поле:" << endl;
        currentPlayer->printGameField(false);
        cout << "\nПоле противника:" << endl;
        opponent->printGameField(true); // Скрываем корабли противника
        
        // Ввод координат (человек или компьютер)
        Coords target;
        if (isCurrentPlayerComputer)
        {
            target = generateComputerShot(*opponent); // TODO: реализовать
        }
        else
        {
            target = getPlayerShot(); // Ввод от человека
        }
        
        // Выстрел
        bool hit = opponent->makeShot(target);
        
        if (hit)
        {
            cout << "Попадание! " << currentPlayer->getName() << " стреляет еще раз." << endl;
            
            // Проверка победы
            if (opponent->getShipsAmount() == 0)
            {
                cout << "\n🎉 ПОБЕДА! " << currentPlayer->getName() << " выиграл!" << endl;
                break;
            }
        }
        else
        {
            cout << "Промах! Ход переходит к " << (currentPlayer == &player1 ? player2.getName() : player1.getName()) << endl;
            
            // Смена игрока
            if (currentPlayer == &player1)
            {
                currentPlayer = &player2;
                opponent = &player1;
                isCurrentPlayerComputer = isPlayer2Computer;
            }
            else
            {
                currentPlayer = &player1;
                opponent = &player2;
                isCurrentPlayerComputer = isPlayer1Computer;
            }
        }
    }
}

Coords getPlayerShot()
{
    string input;
    while (true)
    {
        cout << "Введите координаты для стрельбы (A1, D8 и т.д.): ";
        cin >> input;
        
        if (input.size() >= 2 && input.size() <= 3 && 
            isdigit(input[1]) && (input.size() == 2 || isdigit(input[2])))
        {
            string letter = input.substr(0, 1);
            int x = stoi(input.substr(1));
            
            if (x >= 1 && x <= 10)
            {
                return Coords(x, letter);
            }
        }
        
        cout << "Неверный формат! Введите координаты типа A1, D8 и т.д." << endl;
    }
}



int main()
{
    string name1, name2;
    bool isPlayer1Computer = false;
    bool isPlayer2Computer = false;
    
    cout << "Игра 'Морской бой'" << endl << endl;
    
    // Ввод имени первого игрока
    cout << "Введите имя первого игрока" << endl;
    cout << "(или нажмите Enter для игры против компьютера): ";
    getline(cin, name1);
    if (name1.empty())
    {
        name1 = "Компьютер 1";
        isPlayer1Computer = true;
    }
    
    // Ввод имени второго игрока
    cout << "Введите имя второго игрока" << endl;
    cout << "(или нажмите Enter чтобы играть против компьютера): ";
    getline(cin, name2);
    if (name2.empty())
    {
        name2 = "Компьютер 2";
        isPlayer2Computer = true;
    }
    
    // Создание игроков
    GameField player1(name1);
    GameField player2(name2);
    
    // Определение порядка хода
    srand(time(nullptr));
    int queue = (rand() % 2) + 1;
    
    cout << endl << "===== ФАЗА РАЗМЕЩЕНИЯ КОРАБЛЕЙ =====" << endl;
    
    if (queue == 1)
    {
        cout << "Первым размещает корабли игрок 1 - " << player1.getName() << endl;
        // Размещение кораблей первого игрока
        if (isPlayer1Computer)
        {
            computerShipPlacement(player1);
        }
        else
        {
            manualShipPlacement(player1);
        }
        
        cout << endl << "Теперь размещает корабли игрок 2 - " << player2.getName() << endl;
        // Размещение кораблей второго игрока
        if (isPlayer2Computer)
        {
            computerShipPlacement(player2);
        }
        else
        {
            manualShipPlacement(player2);
        }
    }
    else
    {
        cout << "Первым размещает корабли игрок 2 - " << player2.getName() << endl;
        // Размещение кораблей второго игрока
        if (isPlayer2Computer)
        {
            computerShipPlacement(player2);
        }
        else
        {
            manualShipPlacement(player2);
        }
        
        cout << endl << "Теперь размещает корабли игрок 1 - " << player1.getName() << endl;
        // Размещение кораблей первого игрока
        if (isPlayer1Computer)
        {
            computerShipPlacement(player1);
        }
        else
        {
            manualShipPlacement(player1);
        }
    }
    
    cout << endl << "===== ФАЗА РАЗМЕЩЕНИЯ ЗАВЕРШЕНА =====" << endl;
    
    startBattle(player1, player2, isPlayer1Computer, isPlayer2Computer);
    
    return 0;
}
