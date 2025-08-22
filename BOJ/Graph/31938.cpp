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

#define MAX 200'001
#define endl '\n'
using ll = long long;

#define INF numeric_limits<ll>::max()
using namespace std;

int N{ 0 }, M{ 0 };
vector <vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);
using vertex = tuple<ll, int>;
vector<int> parent(MAX, -1);
ll result{ 0 };

void input()
{
    cin >> N >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };

        cin >> src >> dst >> w;

        edges[src].push_back({ dst,w });
        edges[dst].push_back({ src,w });
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
                if (dist[parent[dst]] < curDist)
                {
                    parent[dst] = src;
                }
            }
        }
    }
}

void solve()
{
    dijkstra();

    for (int i{ 1 }; i <= N; ++i)
    {
        if (parent[i] != -1)
            result += dist[i] - (dist[parent[i]] / 10);
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