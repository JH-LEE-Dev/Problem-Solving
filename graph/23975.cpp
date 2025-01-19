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
using ll = long long;
using vertex = tuple<ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 1'000'001

int N, M, K;
vector < vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);
vector<int> market;
vector<int> query;
vector<int> parent(MAX, 0);

void input()
{
    cin >> N >> M >> K;

    for (int i{ 0 }; i < N; ++i)
    {
        int input;
        cin >> input;

        market.push_back(input);
    }

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };

        cin >> src >> dst >> w;

        edges[src].push_back({ dst,w });
        edges[dst].push_back({ src,w });
    }

    for (int i{ 0 }; i < K; ++i)
    {
        int input{ 0 };
        cin >> input;

        query.push_back(input);
    }
}

void dijkstra()
{
    priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
    pq.push({ 0,1 });
    dist[1] = 0;

    while (pq.empty() == false)
    {
        auto cur{ pq.top() };
        pq.pop();

        auto src{ get<1>(cur) };
        auto curDist{ get<0>(cur) };

        if (dist[src] < curDist)
            continue;

        for (auto& edge : edges[src])
        {
            auto dst{ edge.first };
            auto w{ edge.second };
            auto newDist{ curDist + w };

            if (dist[dst] > newDist)
            {
                dist[dst] = newDist;
                parent[dst] = src;
                pq.push({ newDist,dst });
            }
            else if (dist[dst] == newDist)
            {
                if (parent[dst] < src)
                    parent[dst] = src;
            }
        }
    }
}

int dfs(int prev)
{
    if (prev == 0)
        return 0;

    if (market[prev - 1] != 0)
        return prev;
    else
    {
        parent[prev] = dfs(parent[prev]);
        return parent[prev];
    }
}

void solve()
{
    dijkstra();

    for (auto& v : query)
    {
        auto cursor{ v };

        if (dist[v] == INF)
        {
            cout << -1 << endl;
            continue;
        }

        int result{ dfs(cursor) };

        if (result == 0)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << result << endl;
            --market[result - 1];
        }
    }
}

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}