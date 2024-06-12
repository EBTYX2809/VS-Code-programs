#include <iostream>
// Библиотеки для рандомайзера.
#include <cstdlib>
#include <ctime>
// Библиотека для таймера.
#include <chrono>
#include <thread>
// Библиотека для getch(), дает ввод клавиш.
#include <conio.h>

using namespace std;

// constexpr - Не знаю что это, но без этого не работает.
constexpr int WIDTH_x = 30;
constexpr int HEIGHT_y = 10;

class Snake
{
public:
    // Создание поля.
    char area[HEIGHT_y][WIDTH_x];
    char key; // Переменная принимающая клавиши с клавиатуры.

    // Координаты головы змейки, еды и хвоста змейки:

    int headX = WIDTH_x / 2;
    int headY = HEIGHT_y / 2;
    int eatX;
    int eatY;

    int snakeLength = 0;        // Длина хвоста.
    int tailX[100], tailY[100]; // Массив координат каждого элемента хвоста.

    bool gameOver = false; // Окончание игры.

    void SetArea()
    {
        // Отрисовка змейки на поле:
        for (int y = 0; y < HEIGHT_y; y++)
        {
            for (int x = 0; x < WIDTH_x; x++)
            {
                area[y][x] = ' '; // Заполнение поля пробелами.

                if (y == 0 || y == HEIGHT_y - 1) // Отрисовка верхнего и нижнего полей
                {
                    area[y][x] = '_';
                }
                if (x == 0 || x == WIDTH_x - 1) // Отрисовка боковых
                {
                    area[y][x] = '|';
                }

                if (headX == x && headY == y) // Отрисовка головы
                {
                    area[y][x] = '@';
                }
                if (eatX == x && eatY == y) // Отрисовка еды
                {
                    area[y][x] = '*';
                }
                if (snakeLength > 0) // Отрисовка хвоста
                {
                    for (int k = 0; k < snakeLength; k++)
                    {
                        if (tailX[k] == x && tailY[k] == y)
                        {
                            area[y][x] = '0';
                        }
                    }
                }
            }
        }
        // Не костыль, а дизайн.
        area[0][12] = 'S';
        area[0][13] = 'N';
        area[0][14] = 'A';
        area[0][15] = 'K';
        area[0][16] = 'E';
        ShowArea();
    }
    void SpawnEat()
    {
        // Просто спавнит еду:
        srand(time(nullptr));
        eatX = rand() % 28 + 1;
        eatY = rand() % 8 + 1;
    }
    void ShowArea()
    {
        system("cls");
        // Выводит актуальное состояние поля на экран:
        for (int y = 0; y < HEIGHT_y; y++)
        {
            for (int x = 0; x < WIDTH_x; x++)
            {
                cout << area[y][x];
            }
            cout << endl;
        }
    }
    void Rule()
    {
        // Проверка выхода за границы поля:
        if (headX == 0 || headX == WIDTH_x || headY == 0 || headY == HEIGHT_y)
        {
            gameOver = true;
        }
        // Проверка замыкания змейки:
        for (int k = 0; k < snakeLength; k++)
        {
            if (tailX[k] == headX && tailY[k] == headY)
            {
                gameOver = true;
            }
        }
        // Проверка съеденной еды, спавн новой и увелечение хвоста змейки:
        if (headX == eatX && headY == eatY)
        {
            snakeLength++;
            SpawnEat();
        }
    }
    void Input()
    {
        char temp = key;
        // Проверка нажатой клавиши
        if (_kbhit())
        {
            key = _getch();
            switch (key)
            {
            case 'w':
                headY--;
                break;
            case 'a':
                headX--;
                break;
            case 's':
                headY++;
                break;
            case 'd':
                headX++;
                break;
            case 'q':
                gameOver = true;
            }
        }
        else
        {
            switch (temp)
            {
            case 'w':
                headY--;
                break;
            case 'a':
                headX--;
                break;
            case 's':
                headY++;
                break;
            case 'd':
                headX++;
                break;
            }
        }
    }
    void Logic()
    {
        // Создаем темповые перемнные, сохраняющие нынешнее положение головы змейки.
        int temp1X = tailX[0];
        int temp1Y = tailY[0];
        // Создаем еще одни темповые переменные, которые будут сохранять нынешнее положение актуального элемента хвоста.
        int temp2X, temp2Y;
        // Задаем первому элементу массива хвоста параметры головы змейки.
        tailX[0] = headX;
        tailY[0] = headY;

        // Цикл, который по очереди передает координаты предыдущего элемента нынешнему.
        for (int k = 1; k < snakeLength; k++) // Начинаем с единицы, ибо 0 это голова, обозначеная выше.
        {
            // Записываем положние нынешнего элемента хвоста в темп 2
            temp2X = tailX[k];
            temp2Y = tailY[k];
            // Меняем значение нынешнего элемента хвоста на значение от головы
            tailX[k] = temp1X;
            tailY[k] = temp1Y;
            // Задаем значение для следующей итерации цикла
            temp1X = temp2X;
            temp1Y = temp2Y;
        }

        // Проще говоря, temp 1 - ведущий элемент, temp2 - последующий.
    }
    void GamePlay()
    {
        while (!gameOver)
        {
            SetArea();
            Input();
            Logic();
            Rule();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    void Play()
    {
        SetArea();
        SpawnEat();
        GamePlay();
    }
};

int main()
{
    Snake player1;
    player1.Play();
};