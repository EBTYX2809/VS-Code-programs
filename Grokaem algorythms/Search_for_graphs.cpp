#include <iostream>
#include <string>
#include <unordered_map>
#include <deque>
#include <vector>
#include <algorithm> // для std::find

using namespace std;

void search(const string &name, unordered_map<string, vector<string>> &graph)
{
    deque<string> search_queue;
    search_queue.insert(search_queue.end(), graph[name].begin(), graph[name].end());

    vector<string> searched;

    while (!search_queue.empty())
    {
        string person = search_queue.front();
        search_queue.pop_front();
        if (find(searched.begin(), searched.end(), person) == searched.end())
        {
            if (person == "thom")
            {
                cout << "it's a mango seller\n";
                return;
            }
            else
            {
                search_queue.insert(search_queue.end(), graph[person].begin(), graph[person].end());
                searched.push_back(person);
            }
        }
    }
    cout << "mango seller not found\n";
}

int main()
{
    unordered_map<string, vector<string>> graph;
    graph["you"] = {"alice", "bob", "claire"};
    graph["bob"] = {"anuj", "peggy"};
    graph["alice"] = {"peggy"};
    graph["claire"] = {"thom", "jonny"};
    graph["anuj"] = {};
    graph["peggy"] = {};
    graph["thom"] = {};
    graph["jonny"] = {};

    search("you", graph);

    return 0;
}