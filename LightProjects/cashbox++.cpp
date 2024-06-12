#include <iostream>
#include <string>
#include <map>
using namespace std;

class Goods
{
private:
    map<string, float> goods = {
        {"Milk", 2.89},
        {"Eggs", 4.99},
        {"Bread", 1.49},
        {"Butter", 1.19},
        {"Coca-Cola", 3.50}};
    float money, change;
    float sum = 0;
    string name;
    map<string, float>::iterator it;

public:
    void ShowGoods()
    {
        for (const auto &obj : goods)
        {
            cout << "Name - " << obj.first << "\tPrice = " << obj.second << endl;
        }
    }
    void AddGood(string name, float price)
    {
        goods.emplace(name, price);
    }
    void Buy()
    {
        ShowGoods();
        while (true)
        {
            cout << "Enter good's name. Enter stop to end.\n";
            cin >> name;
            if (name == "stop")
            {
                break;
            }
            it = goods.find(name);
            if (it != goods.end())
            {
                sum += it->second;
                cout << "Added " << name << " costing " << it->second << "$. Total sum: " << sum << "$\n";
            }
            else
            {
                cout << "Good not found. Please enter another one.\n";
            }
        }
        cout << "How much money did the customer give?";
        cin >> money;
        change = money - sum;
        cout << "Your change: " << change << endl;
    }
};

int main()
{
    Goods cusomer1;
    cusomer1.Buy();
}