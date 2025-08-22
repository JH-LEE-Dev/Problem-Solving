#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>
#include <limits>
#include <tuple>

#define endl '\n'
using namespace std;
#define MAX 20'005

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> distances(MAX, numeric_limits<int>::max());

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int V{ 0 }, E{ 0 }, start{ 0 };
    cin >> V >> E >> start;

    for (int i{ 0 }; i < E; ++i)
    {
        int src{ 0 }, dst{ 0 }, weight{ 0 };
        cin >> src >> dst >> weight;
        edges[src].push_back({ dst,weight });
    }

    priority_queue<pair<int, int>> myPQ;

    myPQ.push({ 0, start });
    distances[start] = 0;

    while (myPQ.empty() == false)
    {
        auto cur = myPQ.top();
        myPQ.pop();

        for (auto& it : edges[cur.second])
        {
            int dst = it.first;
            int weight = it.second;

            if (distances[cur.second] + weight < distances[dst])
            {
                distances[dst] = distances[cur.second] + weight;
                myPQ.push({ -distances[dst],dst });
            }
        }
    }

    for (int i{ 1 }; i <= V; ++i)
    {
        if (distances[i] == numeric_limits<int>::max())
        {
            cout << "INF" << endl;
        }
        else
        {
            cout << distances[i] << endl;
        }
    }

    return 0;
}