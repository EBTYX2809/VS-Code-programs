#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

void Test()
{
    srand(time(nullptr));
    string WordsKit[100]{"cat", "dog", "bird", "fish", "mouse", "house", "tree", "car", "bike", "road",
                         "book", "pen", "cup", "door", "window", "chair", "table", "phone", "watch", "shoe",
                         "hat", "shirt", "pants", "sock", "bag", "bed", "box", "key", "lamp", "fork",
                         "spoon", "knife", "plate", "glass", "bottle", "clock", "bell", "wall", "floor", "ceiling",
                         "pillow", "blanket", "desk", "computer", "mousepad", "keyboard", "screen", "picture", "frame", "plant",
                         "flower", "grass", "sun", "moon", "star", "sky", "cloud", "rain", "snow", "wind",
                         "fire", "water", "earth", "air", "stone", "rock", "sand", "soil", "leaf", "branch",
                         "root", "seed", "fruit", "bread", "milk", "egg", "cheese", "butter", "salt", "sugar",
                         "tea", "coffee", "juice", "cake", "pie", "cookie", "jam", "honey", "meat", "rice",
                         "pasta", "soup", "salad", "apple", "banana", "grape", "peach", "plum", "pear", "berry"};

    string TestKit[10];      // Набор отбираемых для теста слов
    int index = 0;           // Номер проверяемого слова
    for (int i = 0; i < 10;) // Проверка уникальности слова
    {
        bool unique;
        unique = true;
        index = rand() % 100;
        for (int j = 0; j < i; j++)
        {
            if (TestKit[j] == WordsKit[index]) // Находит уже выбраное слово и сравнивает со словом по актуальному индексу
            {
                unique = false;
                break;
            }
        }
        if (unique)
        {
            TestKit[i] = WordsKit[index]; // Если функция не сдохла на проверке уникальности просто добавляем слово в набор для теста
            i++;
        }
    }

    for (int i = 0; i < 10; i++) // Визуальное оформеление
    {
        if (i == 9)
        {
            cout << TestKit[i] << ".\n";
            break;
        }
        cout << TestKit[i] << ", ";
    }

    int a;
    int score = 0;
    cout << "Enter 1 to start test, 0 to exit.\n";
    cin >> a;
    if (a == 1)
    {
        string temp;
        auto start = chrono::high_resolution_clock::now(); // Начало таймера
        for (int i = 0; i < 10; i++)                       // Ну и довольно очевидная проверка правильности слова
        {
            cout << "Current word: " << TestKit[i] << endl
                 << endl;
            cout << "Type it: \t";
            cin >> temp;
            if (temp == TestKit[i])
            {
                score++;
            }
        }
        auto end = chrono::high_resolution_clock::now(); // Конец таймера
        chrono::duration<double> duration = end - start; // Подсчет времени
        cout << "Time taken to execute Test: " << duration.count() << " seconds." << endl;
    }
    cout << "Your score " << score << "/10.\n";
}

int main()
{
    Test();
    string a;
    while (a != "Yes")
    {
        cout << "Do you want retry? Yes/No\n";
        cin >> a;
        Test();
    }
}