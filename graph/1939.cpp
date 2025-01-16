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

#define MAX 100'001
#define endl '\n'
#define INF -numeric_limits<ll>::max()

int N{ 0 }, M{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);
int start{ 0 }, goal{ 0 };

using vertex = tuple<ll, int>;

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

    cin >> start >> goal;
}

void dijkstra()
{
    priority_queue<vertex, vector<vertex>, less<vertex>> pq;
    dist[start] = 0;
    pq.push({ 0,start });

    while (pq.empty() == false)
    {
        auto cur{ pq.top() };
        pq.pop();

        auto src{ get<1>(cur) };
        auto curDist{ get<0>(cur) };

        if (dist[src] > curDist)
            continue;

        for (auto& edge : edges[src])
        {
            auto dst{ edge.first };
            auto w{ edge.second };

            if (curDist < w && curDist != 0)
                w = curDist;

            if (dist[dst] < w)
            {
                dist[dst] = w;
                pq.push({ w,dst });
            }
        }
    }
}

void solve()
{
    dijkstra();

    cout << dist[goal];
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}