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

#define MAX 5'001
using namespace std;

#define endl '\n'
#define INF numeric_limits<ll>::max()

using ll = long long;
using vertex = tuple<ll, int, bool>;

int N{ 0 }, M{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
int start{ 0 }, goal{ 0 };
ll total{ 0 };
vector<vector<ll>> dist(MAX, vector <ll>(2, INF));
int maxEdge{ -1 };

void dijkstra()
{
    priority_queue<vertex, vector<vertex>, greater<vertex>> myPQ;
    myPQ.push({ 0,start,false });

    dist[start][false] = 0;

    while (myPQ.empty() == false)
    {
        auto cur{ myPQ.top() };
        myPQ.pop();

        auto src{ get<1>(cur) };
        auto curDist{ get<0>(cur) };
        auto curErase{ get<2>(cur) };

        if (dist[src][curErase] < curDist)
            continue;

        for (auto& edge : edges[src])
        {
            auto dst{ edge.first };
            auto w{ edge.second };
            auto newDist{ curDist + w };

            if (dist[dst][curErase] > newDist)
            {
                dist[dst][curErase] = newDist;

                myPQ.push({ newDist,dst,curErase });
            }

            if (curErase == false)
            {
                if (dist[dst][true] > curDist)
                {
                    dist[dst][true] = curDist;

                    myPQ.push({ curDist,dst,true });
                }
            }
        }
    }

    cout << total - dist[goal][true];
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };
        cin >> src >> dst >> w;

        edges[src].push_back({ dst,w });
        edges[dst].push_back({ src,w });

        total += w;
    }

    cin >> start >> goal;
    dijkstra();

    return 0;
}