#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <unordered_set>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <thread>

using namespace std;

struct Hex // Основной класс клетки
{
    int x;
    int y;

    Hex(int x, int y) : x(x), y(y) {}

    bool operator==(const Hex &other) const
    {
        return x == other.x && y == other.y;
    }

    bool IsNeighbor(const Hex &other) const // Эта функция нужна для прочека того, рядом ли например клетка игрока и монстра
    {
        int dx = abs(x - other.x);
        int dy = abs(y - other.y);
        return (dx == 1 && dy == 0) || (dx == 0 && dy == 1) || (dx == 1 && dy == 1);
    }

    bool IsWithinBounds() const // Проверка находится ли клетка в границах карты
    {
        return x >= 1 && x <= 9 && y >= 1 && y <= 9;
    }

    vector<Hex> GetNeighbors() const // Получение всех соседних клеток, с учетом границ карты
    {
        vector<Hex> neighbors = {
            Hex(x + 1, y),
            Hex(x - 1, y),
            Hex(x, y + 1),
            Hex(x, y - 1),
            Hex(x + 1, y - 1),
            Hex(x - 1, y + 1)};

        vector<Hex> validNeighbors;
        for (const auto &hex : neighbors)
        {
            if (hex.IsWithinBounds())
            {
                validNeighbors.push_back(hex);
            }
        }
        return validNeighbors;
    }
};

struct HexHash
{
    size_t operator()(const Hex &hex) const
    {
        return hash<int>()(hex.x) ^ (hash<int>()(hex.y) << 1);
    }
};

class Player // Класс игрока условный, просто в оригинальный нужно добавить поле Hex position
{
public:
    Hex position = {0, 0};
    Player() : position(0, 0) {}
};

class Monster // Класс монстра тоже условный, дальше можно расширять как угодно
{
public:
    Hex position = {0, 0};
    string name;

    void MoveTo(const Hex &newPosition)
    {
        position = newPosition;
    }
};

class Game // Основной класс в котором происходит все действо. Создан для удобства работы с картой, всеми монстрами и конкретным игроком
{
public:
    vector<vector<Hex>> Map; // Отображение карты и объектов не ней уже отдельно нужно настраивать
    vector<Monster> Monsters;
    Player *m_player;

    Game(Player *player = nullptr) : m_player(player)
    {
        CreateMap(9, 9);
        if (m_player)
        {
            SpawnPlayer(m_player);
        }
        SpawnMonsters(3);
    }

    void CreateMap(int width, int height)
    {
        Map.clear();
        for (int x = 1; x <= width; ++x)
        {
            vector<Hex> row;
            for (int y = 1; y <= height; ++y)
            {
                row.emplace_back(x, y);
            }
            Map.push_back(row);
        }
    }

    void SpawnPlayer(Player *player)
    {
        static mt19937 rng(random_device{}());

        // Если карта с заранее определенными зонами, то проще задать их вручную
        vector<Hex> availableCells = {
            Hex(6, 2),
            Hex(7, 2), Hex(7, 3),
            Hex(8, 2), Hex(8, 3)};

        uniform_int_distribution<size_t> dist(0, availableCells.size() - 1);
        Hex hex = availableCells[dist(rng)];
        player->position = hex;
    }

    void SpawnMonsters(int count)
    {
        for (int i = 0; i < count; ++i)
        {
            Hex coordinates = RandomizeCoordinates();
            Monster monster;
            monster.position = coordinates;
            monster.name = "Monster" + to_string(i + 1);
            Monsters.push_back(monster);
        }
    }

    void MonstersMove()
    {
        unordered_set<Hex, HexHash> occupiedPositions;
        for (const auto &m : Monsters)
        {
            occupiedPositions.insert(m.position);
        }

        for (auto &monster : Monsters)
        {
            auto possibleMoves = monster.position.GetNeighbors(); // Получаем соседей клетки с монстром
            // Удаляем занятые монстрами клетки
            possibleMoves.erase(
                remove_if(possibleMoves.begin(), possibleMoves.end(),
                          [&](const Hex &hex)
                          {
                              return occupiedPositions.count(hex) ||
                                     hex.IsNeighbor(m_player->position);
                          }),
                possibleMoves.end());

            // Сортируем все ближайшие клетки по дистанции к игроку
            sort(possibleMoves.begin(), possibleMoves.end(),
                 [&](const Hex &a, const Hex &b)
                 {
                     return GetDistance(a, m_player->position) <
                            GetDistance(b, m_player->position);
                 });

            if (!possibleMoves.empty())
            {
                occupiedPositions.erase(monster.position);
                // Просто вывод передвижения в консоль
                cout << "Player position: " << m_player->position.x << " " << m_player->position.y << endl;
                cout << "Monster " << monster.name << " moved from: " << monster.position.x << " " << monster.position.y << endl;

                monster.MoveTo(possibleMoves.front());
                // После добавления визуального отображения карты и объектов на ней, можно удалить
                cout << "To: " << monster.position.x << " " << monster.position.y << endl;

                occupiedPositions.insert(possibleMoves.front());
            }

            this_thread::sleep_for(chrono::milliseconds(1000)); // Задержка между движениями монстров
        }
    }

private:
    Hex RandomizeCoordinates()
    {
        static mt19937 rng(random_device{}());
        vector<Hex> availableCells;

        for (int x = 1; x <= 9; ++x)
        {
            for (int y = 1; y <= 9; ++y)
            {
                availableCells.emplace_back(x, y);
            }
        }

        // Опять же, заранее определенные красная и желтые зоны проще занести в список недоступных для спавна вручную
        vector<Hex> unavailableCells = {
            Hex(5, 1), Hex(5, 2), Hex(5, 3),
            Hex(6, 1), Hex(6, 2), Hex(6, 3),
            Hex(7, 1), Hex(7, 2), Hex(7, 3), Hex(7, 4),
            Hex(8, 1), Hex(8, 2), Hex(8, 3), Hex(8, 4),
            Hex(9, 1), Hex(9, 2), Hex(9, 3), Hex(9, 4)};

        // Тут просто удаляются недоступные клетки, красная и желтая зона, и клетки занятые другими монстрами
        availableCells.erase(
            remove_if(availableCells.begin(), availableCells.end(),
                      [&](const Hex &cell)
                      {
                          bool unavailable = any_of(
                              unavailableCells.begin(), unavailableCells.end(),
                              [&](const Hex &zone)
                              {
                                  return cell.x == zone.x && cell.y == zone.y;
                              });
                          bool occupied = any_of(
                              Monsters.begin(), Monsters.end(),
                              [&](const Monster &m)
                              {
                                  return cell.x == m.position.x && cell.y == m.position.y;
                              });
                          return unavailable || occupied;
                      }),
            availableCells.end());

        if (availableCells.empty())
        {
            return Hex(1, 1);
        }

        uniform_int_distribution<size_t> dist(0, availableCells.size() - 1);
        return availableCells[dist(rng)];
    }

    static int GetDistance(const Hex &a, const Hex &b) // Подсчет дистанции между игроком и монстром по формуле гексагонального расстояния
    {
        return (abs(a.x - b.x) + abs(a.y - b.y) +
                abs(a.x - b.x - a.y + b.y)) /
               2;
    }
};

int main()
{
    Player player;
    Game game(&player);

    // Тут создаешь новый поток сфункцией MonstersMove
    thread MovingThread(&Game::MonstersMove, &game);
    // Тут ожидаешь его выполнения и завершения
    MovingThread.join();

    return 0;
}