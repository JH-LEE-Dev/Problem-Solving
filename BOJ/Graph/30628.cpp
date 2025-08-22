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

using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 100'001
#define MAX_NUM 1'000'000'001

int N{ 0 }, M{ 0 }, K{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<bool>> dist(MAX, vector<bool>(12, false));

void input()
{
    cin >> N >> M >> K;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };
        cin >> src >> dst >> w;

        edges[src].push_back({ dst,w });
        edges[dst].push_back({ src,w });
    }
}

bool dijkstra()
{
    priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
    pq.push({ 0,1,0 });

    while (pq.empty() == false)
    {
        auto cur{ pq.top() };
        pq.pop();

        auto src{ get<1>(cur) };
        auto curDist{ get<0>(cur) };
        auto curRemains{ get<2>(cur) };

        if (dist[src][curRemains] == true)
        {
            continue;
        }

        dist[src][curRemains] = true;

        if (src == N)
        {
            if (curDist == K)
                return true;

            if (curRemains == K % 12)
                return true;
        }

        for (auto& edge : edges[src])
        {
            auto dst{ edge.first };
            auto w{ edge.second };
            auto newDist{ curDist + w };
            auto remains{ newDist % 12 };

            if (newDist > K)
                continue;

            if (dist[dst][remains] == false)
            {
                pq.push({ newDist,dst,remains });
            }
        }
    }

    return false;
}

void solve()
{
    if (dijkstra())
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}