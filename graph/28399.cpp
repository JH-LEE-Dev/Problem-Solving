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
#define INF numeric_limits<long long>::max()
using namespace std;

enum STATE
{
    OUT, IN
};

using ll = long long;
using vertex = tuple<ll, int, STATE>;

#define MAX 200'001

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<int>> kPath(MAX / 2 + 1, vector<int>());
int N{ 0 }, M{ 0 }, K{ 0 };
vector<int> nxtVertex(MAX, -1);
vector<bool> startVertex(MAX, false);
vector<vector<ll>> dist(MAX, vector<ll>(2, INF));

void dijkstra()
{
    priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

    if (startVertex[1] == true)
    {
        pq.push({ 0,1,IN });
        dist[1][IN] = 0;
    }
    else
    {
        pq.push({ 0,1,OUT });
        dist[1][OUT] = 0;
    }

    while (pq.empty() == false)
    {
        auto cur{ pq.top() };
        pq.pop();

        auto src{ get<1>(cur) };
        auto curDist{ get<0>(cur) };
        auto curState{ get<2>(cur) };

        if (dist[src][curState] < curDist)
            continue;

        for (auto& edge : edges[src])
        {
            curState = get<2>(cur);

            auto dst{ edge.first };
            auto w{ edge.second };
            auto newDist{ curDist + w };

            if (curState == IN && nxtVertex[src] == dst && nxtVertex[dst] == 0)
                continue;

            if (startVertex[dst] == true)
                curState = IN;
            else
            {
                if (curState == IN)
                {
                    if (nxtVertex[src] == dst)
                        curState = IN;
                    else
                        curState = OUT;
                }
            }

            if (dist[dst][curState] > newDist)
            {
                dist[dst][curState] = newDist;
                pq.push({ newDist,dst,curState });
            }
        }
    }
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
    }

    for (int i{ 0 }; i < K; ++i)
    {
        int num{ 0 };
        cin >> num;

        for (int j{ 0 }; j < num; ++j)
        {
            int input{ 0 };
            cin >> input;

            kPath[i].push_back(input);

            if (j == 0)
            {
                startVertex[input] = true;
            }
            else
            {
                if (j == num - 1)
                {
                    nxtVertex[kPath[i][j]] = 0;
                }

                nxtVertex[kPath[i][j - 1]] = input;
            }
        }
    }

    dijkstra();

    for (int i{ 1 }; i <= N; ++i)
    {
        auto result{ min(dist[i][true],dist[i][false]) };

        if (result == INF)
            cout << -1;
        else
            cout << result;

        cout << ' ';
    }

    return 0;
}