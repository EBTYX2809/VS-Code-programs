#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Функция для восстановления пути от стартового узла до целевого
vector<string> reconstruct_path(const unordered_map<string, string> &came_from, const string &start, const string &goal)
{
    vector<string> path;
    string current = goal;
    while (current != start)
    {
        path.push_back(current);
        current = came_from.at(current);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

// Функция для выполнения поиска в ширину и нахождения кратчайшего пути
vector<string> bfs(const unordered_map<string, vector<string>> &graph, const string &start, const string &goal)
{
    deque<string> search_queue;              // Очередь для хранения узлов, подлежащих посещению
    unordered_map<string, string> came_from; // Хранение предков узлов

    search_queue.push_back(start); // Добавляем начальный узел в очередь
    came_from[start] = "";         // Начальный узел не имеет предка

    while (!search_queue.empty())
    {
        string current = search_queue.front(); // Получаем узел из начала очереди
        search_queue.pop_front();              // Удаляем его из очереди

        if (current == goal)
        {                                                    // Если текущий узел является целевым
            return reconstruct_path(came_from, start, goal); // Восстанавливаем и возвращаем путь
        }

        // Добавляем соседей текущего узла в очередь, если они еще не посещены
        for (const string &neighbor : graph.at(current))
        {
            if (came_from.find(neighbor) == came_from.end())
            {
                search_queue.push_back(neighbor);
                came_from[neighbor] = current; // Устанавливаем предка для соседа
            }
        }
    }

    return {}; // Возвращаем пустой путь, если цель не найдена
}

int main()
{
    // Определяем граф как список смежности
    unordered_map<string, vector<string>> graph;
    graph["A"] = {"B", "C"};
    graph["B"] = {"A", "D", "E"};
    graph["C"] = {"A", "F"};
    graph["D"] = {"B"};
    graph["E"] = {"B", "F"};
    graph["F"] = {"C", "E"};

    string start = "A"; // Начальная вершина
    string goal = "F";  // Целевая вершина

    // Выполняем поиск в ширину для нахождения кратчайшего пути
    vector<string> path = bfs(graph, start, goal);

    // Выводим найденный путь
    if (!path.empty())
    {
        cout << "Shortest path from " << start << " to " << goal << ": ";
        for (const string &node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found from " << start << " to " << goal << "." << endl;
    }

    return 0;
}