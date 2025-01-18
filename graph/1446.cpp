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
#define MAX 10'001

int N{ 0 }, K{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);

void input()
{
    cin >> N >> K;

    for (int i{ 0 }; i < N; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };
        cin >> src >> dst >> w;

        edges[src].push_back({ dst,w });
    }
}

void dijkstra()
{
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({ 0,0 });
    dist[0] = 0;

    while (pq.empty() == false)
    {
        auto cur{ pq.top() };
        pq.pop();

        auto curDist{ get<0>(cur) };
        auto src{ get<1>(cur) };

        if (dist[src] < curDist)
            continue;

        if (src == K)
            break;

        if (edges[src].empty())
        {
            if (dist[src + 1] > dist[src] + 1)
            {
                dist[src + 1] = dist[src] + 1;
                pq.push({ dist[src + 1], src + 1 });
            }
        }
        else
        {
            if (dist[src + 1] > dist[src] + 1)
            {
                dist[src + 1] = dist[src] + 1;
                pq.push({ dist[src + 1], src + 1 });
            }

            for (auto& edge : edges[src])
            {
                auto dst{ edge.first };
                auto w{ edge.second };
                auto newDist{ curDist + w };

                if (dist[dst] > newDist)
                {
                    dist[dst] = newDist;
                    pq.push({ newDist,dst });
                }
            }
        }
    }
}

void solve()
{
    dijkstra();

    cout << dist[K];
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}