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
#include <iomanip>

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N{ 0 }, M{ 0 }, R{ 0 };
vector<int> items(MAX, 0);
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());

int result{ 0 };

using vertex = tuple<int, int>;

void input()
{
    cin >> N >> M >> R;

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> items[i];
    }

    for (int i{ 0 }; i < R; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };
        cin >> src >> dst >> w;

        edges[src].push_back({ dst,w });
        edges[dst].push_back({ src,w });
    }
}

void dijkstra(int start)
{
    vector<int> dist(MAX, INF);
    priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
    pq.push({ 0,start });
    dist[start] = 0;
    int tempResult{ 0 };

    while (pq.empty() == false)
    {
        auto cur{ pq.top() };
        pq.pop();

        auto src{ get<1>(cur) };
        auto curDist{ get<0>(cur) };

        if (dist[src] < curDist)
            continue;

        tempResult += items[src - 1];

        for (auto& edge : edges[src])
        {
            auto dst{ edge.first };
            auto w{ edge.second };
            auto newDist{ curDist + w };

            if (newDist > M)
                continue;

            if (dist[dst] > newDist)
            {
                dist[dst] = newDist;
                pq.push({ newDist,dst });
            }
        }
    }

    result = max(result, tempResult);
}

void solve()
{
    for (int i{ 1 }; i <= N; ++i)
    {
        dijkstra(i);
    }

    cout << result;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}