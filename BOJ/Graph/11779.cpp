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
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 100'005

int V{ 0 }, E{ 0 }, start{ 0 }, goal{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist(MAX, INF);

vector<int> parent(MAX, 0);

void bfs()
{
    priority_queue<pair<int, int>> pQ;
    dist[start] = 0;
    pQ.push({ 0,start });

    while (pQ.empty() == false)
    {
        auto cur = pQ.top();
        pQ.pop();
        int curVertex = cur.second;
        int curDist = -cur.first;

        if (dist[curVertex] < curDist)
            continue;

        for (auto& dst : edges[curVertex])
        {
            int vertex = dst.first;
            int weight = dst.second;
            int newDist = curDist + weight;

            if (dist[vertex] > newDist)
            {
                dist[vertex] = newDist;
                pQ.push({ -newDist,vertex });
                parent[vertex] = curVertex;
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> V >> E;

    for (int i{ 0 }; i < E; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };
        cin >> src >> dst >> w;

        edges[src].push_back({ dst,w });
    }
    cin >> start >> goal;

    bfs();

    stack<int> path;
    int curVertex{ goal };
    while (curVertex != start)
    {
        path.push(curVertex);
        curVertex = parent[curVertex];
    }
    path.push(curVertex);

    cout << dist[goal] << endl;
    cout << path.size() << endl;
    while (path.empty() == false)
    {
        cout << path.top() << " ";
        path.pop();
    }

    return 0;
}