#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
using namespace std;

int main()
{
    string path = "Count_words_in_text.txt"; // Указываем путь к тектовому файлу
    map<string, int> counter;                // Создаем контейнер пар, string - слово, int - количество его в тексте.

    ifstream f;
    f.open(path);

    if (!f.is_open()) // Проверка на то, открывается ли файл
    {
        cout << "Erorr opening file\n";
    }
    else
    {
        cout << "File opened\n";
    }

    map<string, int>::iterator it; // Задаем итератор

    string str;
    while (!f.eof()) // Основной цикл. Работает до конца файла.
    {
        str = "";
        f >> str; // Записываем считываемое значение в переменную str

        str.erase(remove_if(str.begin(), str.end(), [](char c)
                            { return c == '.' || c == ','; }), // Удаляет точку и запятую в считываемых словах что бы не было путаницы.
                  str.end());

        it = counter.find(str); // Ищем в контенйнере такой же элемент и записываем его в итератор.

        if (it != counter.end()) // Если итератор найдет одинаковый элемент
        {
            it->second++; // То его количество увеличится.
        }
        else
        {
            counter.emplace(str, 1); // Если блок if не отрабатывает, то просто записываем слово в str, и даем ему количество 1.
        }
    }

    for (const auto &obj : counter) // Вывод всех данных в консоль.
    {
        cout << "Word: " << obj.first << " Count: " << obj.second << endl;
    }
}