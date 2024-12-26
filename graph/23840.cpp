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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

using ll = long long;
using vertex = tuple<ll, int, int>;
#define MAX 100'001
int N{ 0 }, M{ 0 }, K{ 0 };
int start{ 0 }, goal{ 0 };
vector<bool> stopBy(MAX, false);
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<ll>> dist(MAX, vector<ll>((1 << 21), INF));

void dijkstra()
{
    priority_queue<vertex, vector<vertex>, greater<vertex>>myPQ;
    myPQ.push({ 0,start,1 });
    dist[start][1] = 0;

    while (myPQ.empty() == false)
    {
        auto cur{ myPQ.top() };
        myPQ.pop();

        auto src{ get<1>(cur) };
        auto curDist{ get<0>(cur) };
        auto curBit{ get<2>(cur) };

        if (dist[src][curBit] < curDist)
            continue;

        for (auto& edge : edges[src])
        {
            auto dst{ edge.first };
            auto w{ edge.second };
            auto newDist{ curDist + w };

            if (stopBy[dst] == true)
            {
                if ((curBit & (1 << dst)) == (1 << dst))
                {
                    if (dist[dst][curBit] > newDist)
                    {
                        myPQ.push({ newDist,dst,curBit });
                        dist[dst][curBit] = newDist;
                    }
                }
                else
                {
                    if (dist[dst][curBit | (1 << dst)] > newDist)
                    {
                        myPQ.push({ newDist,dst,curBit | (1 << dst) });
                        dist[dst][curBit | (1 << dst)] = newDist;
                    }
                }
            }
            else
            {
                if (dist[dst][curBit] > newDist)
                {
                    myPQ.push({ newDist,dst,curBit });
                    dist[dst][curBit] = newDist;
                }
            }
        }
    }

    cout << dist[goal][(1 << (K + 1)) - 1];
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M >> K;

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

        stopBy[input] = false;
    }

    dijkstra();

    return 0;
}