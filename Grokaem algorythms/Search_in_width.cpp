#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <set>

using namespace std;

// Функция для выполнения поиска в ширину
void bfs(const unordered_map<string, vector<string>> &graph, const string &start, const string &goal)
{
    deque<string> search_queue;    // Очередь для хранения узлов, подлежащих посещению
    search_queue.push_back(start); // Добавляем начальный узел в очередь

    set<string> visited;   // Множество для хранения посещенных узлов
    visited.insert(start); // Помечаем начальный узел как посещенный

    while (!search_queue.empty())
    {
        string current = search_queue.front(); // Получаем узел из начала очереди
        search_queue.pop_front();              // Удаляем его из очереди

        if (current == goal)
        { // Если текущий узел является целевым
            cout << "Found the goal: " << goal << endl;
            return;
        }

        // Добавляем соседей текущего узла в очередь, если они еще не посещены
        for (const string &neighbor : graph.at(current))
        {
            if (visited.find(neighbor) == visited.end())
            {
                search_queue.push_back(neighbor);
                visited.insert(neighbor); // Помечаем соседа как посещенного
            }
        }
    }

    cout << "Goal not found in the graph." << endl;
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

    // Выполняем поиск в ширину
    bfs(graph, start, goal);

    return 0;
}