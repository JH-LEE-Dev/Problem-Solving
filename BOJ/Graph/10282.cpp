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
using vertex = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 10'001

int T{ 0 };
int N{ 0 }, M{ 0 }, K{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist(MAX, INF);

void input()
{
    cin >> T;
}

void dijkstra()
{
    priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
    pq.push({ 0,K });
    dist[K] = 0;

    int counting{ 0 };
    int maxTime{ 0 };

    while (pq.empty() == false)
    {
        auto cur{ pq.top() };
        pq.pop();

        auto src{ get<1>(cur) };
        auto curDist{ get<0>(cur) };

        if (dist[src] < curDist)
            continue;

        ++counting;

        maxTime = max(maxTime, curDist);

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

    cout << counting << ' ' << maxTime << endl;
}

void solve()
{
    while (T != 0)
    {
        edges = vector<vector<pair<int, int>>>(MAX, vector<pair<int, int>>());
        dist = vector<int>(MAX, INF);

        cin >> N >> M >> K;

        for (int i{ 0 }; i < M; ++i)
        {
            int dst{ 0 }, src{ 0 }, w{ 0 };
            cin >> dst >> src >> w;

            edges[src].push_back({ dst,w });
        }

        dijkstra();

        --T;
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