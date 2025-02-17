#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;

class Graph
{
public:
    void add_edge(const string &from, const string &to, int weight)
    {
        edges[from][to] = weight;
    }

    const unordered_map<string, int> &neighbors(const string &node) const
    {
        return edges.at(node);
    }

    vector<string> get_nodes() const
    {
        vector<string> keys;
        for (const auto &pair : edges)
        {
            keys.push_back(pair.first);
        }
        return keys;
    }

private:
    unordered_map<string, unordered_map<string, int>> edges;
};

string find_lowest_cost_node(const unordered_map<string, int> &costs, const set<string> &processed)
{
    int lowest_cost = INT_MAX;
    string lowest_cost_node;
    for (const auto &pair : costs)
    {
        int cost = pair.second;
        if (cost < lowest_cost && processed.find(pair.first) == processed.end())
        {
            lowest_cost = cost;
            lowest_cost_node = pair.first;
        }
    }
    return lowest_cost_node;
}

vector<string> dijkstra(const Graph &graph, const string &start, const string &end)
{
    unordered_map<string, int> costs;
    unordered_map<string, string> parents;
    set<string> processed;

    for (const string &node : graph.get_nodes())
    {
        if (node == start)
        {
            costs[node] = 0;
        }
        else
        {
            costs[node] = INT_MAX;
        }
        parents[node] = "";
    }

    string node = find_lowest_cost_node(costs, processed);
    while (!node.empty())
    {
        int cost = costs[node];
        const auto &neighbors = graph.neighbors(node);

        for (const auto &pair : neighbors)
        {
            string neighbor = pair.first;
            int new_cost = cost + pair.second;
            if (new_cost < costs[neighbor])
            {
                costs[neighbor] = new_cost;
                parents[neighbor] = node;
            }
        }

        processed.insert(node);
        node = find_lowest_cost_node(costs, processed);
    }

    vector<string> path;
    for (string at = end; !at.empty(); at = parents[at])
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    Graph graph;
    graph.add_edge("start", "a", 6);
    graph.add_edge("start", "b", 2);
    graph.add_edge("a", "fin", 1);
    graph.add_edge("b", "a", 3);
    graph.add_edge("b", "fin", 5);

    vector<string> path = dijkstra(graph, "start", "fin");

    cout << "Shortest path: ";
    for (const string &node : path)
    {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
