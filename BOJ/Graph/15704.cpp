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
#define MAX 100'001
#define endl '\n'
#define INF numeric_limits<ll>::max()

int N{ 0 }, M{ 0 }, K{ 0 };
vector<vector<tuple<int, int, int>>> edges(MAX, vector<tuple<int, int, int>>());

void input()
{
    cin >> N >> M >> K;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 }, t{ 0 };
        cin >> src >> dst >> w >> t;

        edges[src].push_back({ dst,w,t });
        edges[dst].push_back({ src,w,t });
    }
}

bool dijkstra(ll num)
{
    vector<ll> dist(MAX, INF);
    dist[1] = 0;
    vector<bool> visited(MAX, false);
    visited[1] = true;

    priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
    pq.push({ 0,1 });

    while (pq.empty() == false)
    {
        auto cur{ pq.top() };
        pq.pop();

        auto src{ get<1>(cur) };
        auto curDist{ get<0>(cur) };

        if (dist[src] < curDist)
            continue;

        if (src == N)
        {
            return true;
        }

        for (auto& edge : edges[src])
        {
            auto dst{ get<0>(edge) };
            auto w{ get<1>(edge) };
            auto t{ get<2>(edge) };

            if (t >= num)
            {
                auto newDist{ curDist };

                if (newDist > K)
                    continue;

                if (dist[dst] > newDist)
                {
                    dist[dst] = newDist;
                    pq.push({ newDist,dst });
                }
            }
            else
            {
                auto newDist{ curDist + w * ((num - t) * (num - t)) };

                if (newDist > K)
                    continue;

                if (dist[dst] > newDist)
                {
                    dist[dst] = newDist;
                    pq.push({ newDist,dst });
                }
            }
        }
    }

    return false;
}

void binarySearch()
{
    ll left{ 1 };
    ll right{ MAX };
    ll middle{ 0 };
    ll result{ 0 };

    while (left <= right)
    {
        middle = (left + right) / 2;

        if (dijkstra(middle))
        {
            left = middle + 1;
            result = middle;
        }
        else
        {
            right = middle - 1;
        }
    }

    cout << result;
}

void solve()
{
    binarySearch();
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}