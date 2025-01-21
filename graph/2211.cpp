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
#define MAX 1'001

int N{ 0 }, M{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist(MAX, INF);
vector<pair<int, int>> result;

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
    pq.push({ 0,1,1 });
    dist[1] = 0;

    while (pq.empty() == false)
    {
        auto cur{ pq.top() };
        pq.pop();

        auto src{ get<1>(cur) };
        auto curDist{ get<0>(cur) };
        auto prev{ get<2>(cur) };

        if (dist[src] < curDist)
            continue;

        if (curDist != 0)
            result.push_back({ src,prev });

        for (auto& edge : edges[src])
        {
            auto dst{ edge.first };
            auto w{ edge.second };
            auto newDist{ curDist + w };

            if (dist[dst] > newDist)
            {
                pq.push({ newDist,dst,src });
                dist[dst] = newDist;
            }
        }
    }
}

void solve()
{
    dijkstra();

    cout << result.size() << endl;
    for (auto& e : result)
    {
        cout << e.first << ' ' << e.second << endl;
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