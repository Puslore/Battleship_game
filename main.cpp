#include "./headers/GameField.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;


void manualShipPlacement(GameField& player);
void computerShipPlacement(GameField& player);
void startBattle(GameField& player1, GameField& player2, bool isPlayer1Computer, bool isPlayer2Computer);
Coords getPlayerShot();
Coords generateComputerShot(GameField& opponent);
void giveHelp();
void newHistoryFile();
void writeToFile(const string& text);


// Подсказка игроку
void giveHelp()
{cout << "\n----------ПОДСКАЗКА" << endl;}


// Очистка файла
void newHistoryFile()
{
    ofstream file("game_history.txt");
    file << "----------ИСТОРИЯ ИГРЫ МОРСКОЙ БОЙ" << endl << endl;
    file.close();
}


// Запись в файл 
void writeToFile(const string& text)
{
    ofstream file("game_history.txt", ios::app);
    file << text << endl;
    file.close();
}


// Функция генерации случайного выстрела компьютера
Coords generateComputerShot(GameField& opponent)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(nullptr));
        initialized = true;
    }
    
    string columns[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    Coords target;
    int attempts = 0;
    
    // Генерация случайных координат до тех пор, пока не найдена неатакованная клетка
    do
    {
        int x = rand() % 10 + 1;
        string y = columns[rand() % 10];
        target = Coords(x, y);
        attempts++;
        
        // Защита от бесконечного цикла
        if (attempts > 100) break;
        
    } while (opponent.isAlreadyShot(target));
    
    cout << "Компьютер стреляет по " << target.y << target.x;
    return target;
}


// Функция ручного размещения кораблей
void manualShipPlacement(GameField& player)
{
    player.printGameField(false);
    cout << player.getName() << ", расставьте корабли!" << endl;
    
    // Предложение автоматического размещения
    cout << "Хотите разместить корабли автоматически? (y/n): ";
    string choice;
    cin >> choice;
    
    if (choice == "y" || choice == "Y" || choice == "да" || choice == "Да")
    {
        player.placeShipsRandomly();
        cout << "Корабли размещены автоматически!" << endl;
        player.printGameField(false);
        return;
    }
    
    while (player.getShipsAmount() < 10)
    {
        cout << "Введите тип корабля(1 - однопалубный и т.д.): ";
        int shipType;
        if (!(cin >> shipType))
        {
            cout << "Ошибка чтения ввода! Введите число от 1 до 4" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
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
                    string inp;
                    cout << "Введите координаты корабля(A1, D8 и т.д.): ";
                    cin >> inp;

                    if (inp.size() < 2 || inp.size() > 3 ||
                        !isdigit(inp[1]) ||
                        (inp.size() == 3 && !isdigit(inp[2])))
                    {
                        cout << "Неправильный формат ввода! Введите A1, D8 и т.д." << endl;
                        continue;
                    }

                    string letter = inp.substr(0, 1);
                    int x = stoi(inp.substr(1));
                    
                    // Добавление проверки диапазона
                    if (x < 1 || x > 10)
                    {
                        cout << "Номер строки должен быть от 1 до 10!" << endl;
                        continue;
                    }

                    if (player.placeShip(Ship(1, vector<Coords>{Coords(x, letter)})))
                    {
                        player.printGameField(false);
                        cout << "Торпедоносец " << inp << " добавлен" << endl;
                    }else
                    {
                        cout << "Ошибка размещения корабля! Попробуйте снова." << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }else cout << "У вас уже есть 4 торпедоносца, выберите другой!" << endl;
            break;

            case 2:
                if (player.getShipsAmount(2) < 3)
                {
                    vector<Coords> coords = {};
                    while (coords.size() < 2)
                    {
                        string inp;
                        cout << "Введите координаты " << (coords.size() + 1) << "-й палубы корабля (A1, D8 и т.д.): ";
                        cin >> inp;
                        
                        if (inp.size() < 2 || !isdigit(inp[1]))
                        {
                            cout << "Неправильный формат ввода! Введите A1, D8 и т.д." << endl;
                            continue;
                        }

                        string letter = inp.substr(0, 1);
                        int x = stoi(inp.substr(1));
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
                    }else
                    {
                        cout << "Ошибка размещения корабля! Попробуйте снова." << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }else cout << "У вас уже есть 3 эсминца, выберите другой!" << endl;
            break;

            case 3:
                if (player.getShipsAmount(3) < 2)
                {
                    vector<Coords> coords = {};
                    while (coords.size() < 3)
                    {
                        string inp;
                        cout << "Введите координаты " << (coords.size() + 1) << "-й палубы корабля (A1, D8 и т.д.): ";
                        cin >> inp;
                        
                        if (inp.size() < 2 || !isdigit(inp[1]))
                        {
                            cout << "Неправильный формат ввода! Введите A1, D8 и т.д." << endl;
                            continue;
                        }

                        string letter = inp.substr(0, 1);
                        int x = stoi(inp.substr(1));
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
                    }else
                    {
                        cout << "Ошибка размещения корабля! Попробуйте снова." << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }else cout << "У вас уже есть 2 крейсера, выберите другой!" << endl;
            break;

            case 4:
                if (player.getShipsAmount(4) < 1)
                {
                    vector<Coords> coords = {};
                    while (coords.size() < 4)
                    {
                        string inp;
                        cout << "Введите координаты " << (coords.size() + 1) << "-й палубы корабля (A1, D8 и т.д.): ";
                        cin >> inp;
                        
                        if (inp.size() < 2 || !isdigit(inp[1]))
                        {
                            cout << "Неправильный формат ввода! Введите A1, D8 и т.д." << endl;
                            continue;
                        }

                        string letter = inp.substr(0, 1);
                        int x = stoi(inp.substr(1));
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
                    }else
                    {
                        cout << "Ошибка размещения корабля! Попробуйте снова." << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }else cout << "У вас уже есть 1 линкор, выберите другой!" << endl;
            break;

            default:
                cout << "Неверный тип корабля!" << endl;
        }
    }
    
    cout << "Размещение кораблей завершено!" << endl;
    player.printGameField(false);
}


// Функция размещения кораблей компьютером
void computerShipPlacement(GameField& player)
{
    cout << "Компьютер " << player.getName() << " размещает корабли..." << endl;
    player.placeShipsRandomly();
    cout << "Компьютер " << player.getName() << " завершил размещение кораблей!" << endl;
    cout << "Поле компьютера:" << endl;
    player.printGameField(false);
}


// Функция получения координат выстрела от игрока
Coords getPlayerShot()
{
    string input;
    while (true)
    {
        cout << "Введите координаты для стрельбы (A1, D8 и т.д.) или 'ПОМОЩЬ': ";
        cin >> input;
        
        // Проверка на команду помощи
        if (input == "ПОМОЩЬ" || input == "помощь" || input == "HELP" || input == "help")
        {
            giveHelp();
            continue;
        }
        
        if (input.size() >= 2 && input.size() <= 3 &&
            isdigit(input[1]) && (input.size() == 2 || isdigit(input[2])))
        {
            string letter = input.substr(0, 1);
            int x = stoi(input.substr(1));
            if (x >= 1 && x <= 10)
            {
                bool validLetter = false;
                string validLetters[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
                for (int i = 0; i < 10; i++)
                {
                    if (letter == validLetters[i])
                    {
                        validLetter = true;
                        break;
                    }
                }
                
                if (validLetter)
                    return Coords(x, letter);
                else
                {
                    cout << "Неверная буква! Используйте A-J." << endl;
                    continue;
                }
            }else
            {
                cout << "Номер строки должен быть от 1 до 10!" << endl;
                continue;
            }
        }
        
        cout << "Неверный формат! Введите координаты типа A1, D8 и т.д." << endl;
    }
}


// Главная функция боевой фазы
void startBattle(GameField& player1, GameField& player2, bool isPlayer1Computer, bool isPlayer2Computer)
{
    cout << "\n----------НАЧАЛО БОЕВОЙ ФАЗЫ" << endl;
    
    // Случайный выбор кто начинает стрелять
    srand(time(nullptr));
    bool isPlayer1Turn = (rand() % 2 == 0);
    cout << "Первым стреляет: " << (isPlayer1Turn ? player1.getName() : player2.getName()) << endl;
    
    while (player1.getShipsAmount() > 0 && player2.getShipsAmount() > 0)
    {
        GameField& currentPlayer = isPlayer1Turn ? player1 : player2;
        GameField& opponent = isPlayer1Turn ? player2 : player1;
        bool isCurrentPlayerComputer = isPlayer1Turn ? isPlayer1Computer : isPlayer2Computer;
        
        cout << "\n----------ХОД ИГРОКА: " << currentPlayer.getName() << endl;
        
        cout << "\nВаше поле:" << endl;
        currentPlayer.printGameField(false);
        cout << "\nПоле противника:" << endl;
        opponent.printGameField(true);
        
        Coords target;
        if (isCurrentPlayerComputer)    
            target = generateComputerShot(opponent);    
        else target = getPlayerShot();   
        
        cout << "\nВыстрел по " << target.y << target.x << ": ";
        cout.flush();
        
        bool hit = opponent.makeShot(target);
        
        if (hit)
        {
            // Проверка окончания игры
            if (opponent.getShipsAmount() == 0)
            {
                // Логирование победного выстрела с пометкой "игра окончена"
                string logEntry = currentPlayer.getName() + " - " + target.y + to_string(target.x) + " - попал - игра окончена";
                writeToFile(logEntry);
                
                cout << "\n----------ИГРА ОКОНЧЕНА" << endl;
                cout << "ПОБЕДИТЕЛЬ: " << currentPlayer.getName() << "!" << endl;
                
                // Запись результатов игры в файл
                writeToFile("");
                writeToFile("----------РЕЗУЛЬТАТ ИГРЫ");
                writeToFile(currentPlayer.getName() + " - победа - осталось кораблей: " + to_string(currentPlayer.getShipsAmount()));
                writeToFile("------------------------------------------");
                
                return;
            }else
            {
                // Обычное попадание
                string logEntry = currentPlayer.getName() + " - " + target.y + to_string(target.x) + " - попал";
                writeToFile(logEntry);
                cout << currentPlayer.getName() << " попал! Стреляет еще раз." << endl;
            }
        }else
        {
            // Промах
            string logEntry = currentPlayer.getName() + " - " + target.y + to_string(target.x) + " - мимо";
            writeToFile(logEntry);
            cout << "Ход переходит к " << (isPlayer1Turn ? player2.getName() : player1.getName()) << endl;
            isPlayer1Turn = !isPlayer1Turn;
        }
        
        // Пауза между ходами разных игроков
        if (!hit && !isCurrentPlayerComputer)
        {
            cout << "\nНажмите Enter для передачи хода...";
            cin.ignore();
            cin.get();
        }
    }
}


int main()
{
    // Инициализация файла лога в самом начале
    newHistoryFile();
    
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
    
    cout << endl << "----------ФАЗА РАЗМЕЩЕНИЯ КОРАБЛЕЙ" << endl;
    
    if (queue == 1)
    {
        cout << "Первым размещает корабли игрок 1 - " << player1.getName() << endl;
        
        if (isPlayer1Computer)
            computerShipPlacement(player1);
        else manualShipPlacement(player1);
        
        cout << endl << "Теперь размещает корабли игрок 2 - " << player2.getName() << endl;
        
        if (isPlayer2Computer)
            computerShipPlacement(player2);
        else manualShipPlacement(player2);
    }
    else
    {
        cout << "Первым размещает корабли игрок 2 - " << player2.getName() << endl;
        
        if (isPlayer2Computer)
            computerShipPlacement(player2);
        else manualShipPlacement(player2);

        cout << endl << "Теперь размещает корабли игрок 1 - " << player1.getName() << endl;
        
        if (isPlayer1Computer)
            computerShipPlacement(player1);
        else manualShipPlacement(player1);
    }

    cout << endl << "----------ФАЗА РАЗМЕЩЕНИЯ ЗАВЕРШЕНА" << endl;
    startBattle(player1, player2, isPlayer1Computer, isPlayer2Computer);
    
    cout << "\nИстория игры сохранена в файл 'game_history.txt'" << endl;
    
    return 0;
}
