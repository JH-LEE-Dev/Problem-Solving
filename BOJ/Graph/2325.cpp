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

#define endl '\n'
#define INF numeric_limits<long long>::max()
using namespace std;

#define MAX 1'001

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<long long> dist(MAX, INF);
vector<pair<int, int>> erased;
vector<int> parent(MAX, -1);

int N{ 0 }, M{ 0 };
long long result{ -1 };

void dijkstra()
{
    dist[1] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> myPQ;
    myPQ.push({ 0,1 });

    while (myPQ.empty() == false)
    {
        auto cur = myPQ.top();
        myPQ.pop();

        auto src{ cur.second };
        auto curDist{ cur.first };

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
                myPQ.push({ newDist,dst });
                parent[dst] = src;
            }
        }
    }

    auto cursor{ N };
    while (cursor != -1)
    {
        auto src{ parent[cursor] };
        erased.push_back({ src,cursor });
        cursor = src;
    }
}

void dijkstra_result()
{
    for (auto& erasedEdge : erased)
    {
        dist = vector<long long>(MAX, INF);
        dist[1] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> myPQ;
        myPQ.push({ 0,1 });

        while (myPQ.empty() == false)
        {
            auto cur = myPQ.top();
            myPQ.pop();

            auto src{ cur.second };
            auto curDist{ cur.first };

            if (dist[src] < curDist)
                continue;

            for (auto& edge : edges[src])
            {
                auto dst{ edge.first };
                auto w{ edge.second };
                auto newDist{ curDist + w };

                if ((src == erasedEdge.first && dst == erasedEdge.second) || (src == erasedEdge.second && dst == erasedEdge.first))
                    continue;

                if (dist[dst] > newDist)
                {
                    dist[dst] = newDist;
                    myPQ.push({ newDist,dst });
                }
            }
        }

        result = max(result, dist[N]);
    }

    cout << result;
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
    }

    dijkstra();
    dijkstra_result();

    return 0;
}