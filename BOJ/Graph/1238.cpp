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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 10'000
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist(MAX, INF);
vector<int> dist_X(MAX, INF);
int N{ 0 }, M{ 0 }, X{ 0 };

void dijkstra(int start)
{
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQ;
    pQ.push({ 0,start });

    while (pQ.empty() == false)
    {
        auto cur = pQ.top();
        pQ.pop();
        auto curVertex = cur.second;
        auto curDist = cur.first;

        if (curDist > dist[curVertex])
            continue;

        for (auto& edge : edges[curVertex])
        {
            auto dst = edge.first;
            auto weight = edge.second;

            if (curDist + weight < dist[dst])
            {
                dist[dst] = curDist + weight;
                pQ.push({ dist[dst],dst });
            }
        }
    }
}

void dijkstra_X(int start)
{
    dist_X[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQ;
    pQ.push({ 0,start });

    while (pQ.empty() == false)
    {
        auto cur = pQ.top();
        pQ.pop();
        auto curVertex = cur.second;
        auto curDist = cur.first;

        if (curDist > dist_X[curVertex])
            continue;

        for (auto& edge : edges[curVertex])
        {
            auto dst = edge.first;
            auto weight = edge.second;

            if (curDist + weight < dist_X[dst])
            {
                dist_X[dst] = curDist + weight;
                pQ.push({ dist_X[dst],dst });
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M >> X;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };
        cin >> src >> dst >> w;
        edges[src].push_back({ dst,w });
    }

    int result{ -1 };
    dijkstra_X(X);

    for (int i{ 1 }; i <= N; ++i)
    {
        dist = vector<int>(MAX, INF);
        if (i == X)
            continue;

        dijkstra(i);

        auto sum = dist[X] + dist_X[i];
        result = max(result, sum);
    }

    cout << result;

    return 0;
}