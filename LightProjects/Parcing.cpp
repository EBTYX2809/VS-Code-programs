#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

class Parser
{
private:
    string expression; // Выражение, которое пользователь вводит.
    int it;            // Итератор отвечающий за определение позиции в выражении, которое нужно считать.

    bool stringNotEnd() // Проверка на конец строки
    {
        return it < expression.size();
    }

    void skipSpace() // Пропуск пробелов
    {
        while (stringNotEnd() && isspace(expression[it]))
        {
            it++;
        }
    }

    int ParserPower(int num)
    {
        while (stringNotEnd(), expression[it] == '^') // Считывание степеня
        {
            it++;                   // После обнаружения степени идем дальше по цифрам.
            int a = ParserNumber(); // Достает сам степень
            num = pow(num, a);      // Уже готове число из прошлых вычислений возводим в нужный степень
        }
        return num;
    }

    int ParserNumber() // Изначальаня функция считывания номера из строки
    {
        int num = 0;
        while (isdigit(expression[it])) // Работает пока isdigit видит в строке цифру
        {
            num = num * 10 + (expression[it] - '0'); // Тут работает на ASCII и добалвяет новые десятки через банальное умножение на 10
            it++;
        }
        ParserPower(num); // Проверяем и делаем возведение в степень если нужно
        return num;
    }

    int ParserSymbol() // Подсчет () и изъятие чисел
    {
        skipSpace();
        if (stringNotEnd() && isdigit(expression[it]))
        {
            return ParserNumber(); // Тут просто считывает число
        }
        else if (stringNotEnd() && expression[it] == '(') // А тут очевидно скобки
        {
            it++; // Скипаем (
            int result = ParserCounting();
            it++;                // Скипаем )
            ParserPower(result); // Проверяем и делаем возведение в степень если нужно
            return result;
        }
        else
        {
            return 0;
        }
    }

    int ParserMultiplication() // Подсчет * и /
    {
        int result = ParserSymbol(); // Сначала записываем в result первую операнду
        skipSpace();
        while (stringNotEnd() && (expression[it] == '*' || expression[it] == '/'))
        {
            char op = expression[it]; // Тут передаем в ор актуальный оператор и переходим к следующему символу
            it++;
            skipSpace();
            int symbol = ParserSymbol(); // Считываем вторую операнду
            if (op == '*')
            {
                result *= symbol; // Ну и производим соответствующую операцию
            }
            else
            {
                result /= symbol;
            }
        }
        return result;
    }

    int ParserCounting() // Общий подсчет и учитывание + -
    {
        int result = ParserMultiplication(); // Сначала записываем в result первую операнду
        skipSpace();
        while (stringNotEnd() && (expression[it] == '+' || expression[it] == '-'))
        {
            char op = expression[it]; // Тут передаем в ор актуальный оператор и переходим к следующему символу
            it++;
            skipSpace();
            int symbol = ParserMultiplication(); // Считываем вторую операнду
            if (op == '+')
            {
                result += symbol; // Ну и производим соответствующую операцию
            }
            else
            {
                result -= symbol;
            }
        }
        return result;
    }

public:
    Parser(const string &expr) : expression(expr), it(0) {}

    int count()
    {
        return ParserCounting();
    }
};

int main()
{
    string expr;
    cout << "Enter your expression: ";
    cin >> expr;
    Parser first(expr);
    int result = first.count();
    cout << expr << " = " << result << endl;
}
