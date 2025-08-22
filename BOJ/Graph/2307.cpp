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
#include <string>
#include <cmath>
#include <bitset>

#define endl '\n'
#define INF numeric_limits<long long>::max()
using namespace std;
#define MAX 1'001
int N{ 0 }, M{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<pair<int, int>> edgesToStop;
vector<int> parent(MAX, -1);
long long minDist{ INF };
long long result{ 0 };

bool isStopedEdge(pair<int, int> edge, pair<int, int> toStop)
{
    return ((edge.first == toStop.first && edge.second == toStop.second) || (edge.first == toStop.second && edge.second == edge.first));
}

void firstDijkstra()
{
    vector<long long> dist(MAX, INF);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> myPQ;
    dist[1] = 0;
    myPQ.push({ 0,1 });

    while (myPQ.empty() == false)
    {
        auto cur = myPQ.top();
        myPQ.pop();

        auto src = cur.second;
        auto curDist = cur.first;

        if (curDist > dist[src])
            continue;

        for (auto& edge : edges[src])
        {
            auto dst = edge.first;
            auto w = edge.second;
            auto newDist = curDist + w;

            if (dist[dst] > newDist)
            {
                dist[dst] = newDist;
                myPQ.push({ newDist,dst });
                parent[dst] = src;
            }
        }
    }

    minDist = dist[N];

    auto cursor = N;
    while (cursor != -1)
    {
        edgesToStop.push_back({ parent[cursor],cursor });
        cursor = parent[cursor];
    }
}

void dijkstra(pair<int, int> toStop)
{
    vector<long long> dist(MAX, INF);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> myPQ;
    dist[1] = 0;
    myPQ.push({ 0,1 });

    while (myPQ.empty() == false)
    {
        auto cur = myPQ.top();
        myPQ.pop();

        auto src = cur.second;
        auto curDist = cur.first;

        if (curDist > dist[src])
            continue;

        for (auto& edge : edges[src])
        {
            auto dst = edge.first;
            auto w = edge.second;
            auto newDist = curDist + w;

            if (isStopedEdge({ src,dst }, toStop))
                continue;

            if (dist[dst] > newDist)
            {
                dist[dst] = newDist;
                myPQ.push({ newDist,dst });
            }
        }
    }

    if (dist[N] == INF)
    {
        result = -1;
    }
    else
    {
        result = max(dist[N] - minDist, result);
    }
}

void func()
{
    firstDijkstra();

    for (auto& edgeToStop : edgesToStop)
    {
        dijkstra(edgeToStop);

        if (result == -1)
        {
            cout << result;
            return;
        }
    }

    cout << result;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };
        cin >> src >> dst >> w;

        edges[src].push_back({ dst,w });
        edges[dst].push_back({ src,w });
    }

    func();

    return 0;
}