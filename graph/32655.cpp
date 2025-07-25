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
#define MAX 51
vector<tuple<int, int, int>> edges;
vector<vector<int>> edgeMatrix(MAX, vector<int>());
vector<int> moneyToEarn;
vector<long long> dist(MAX, -INF);
int N{ 0 }, M{ 0 };
int start{ 0 }, goal{ 0 };

unordered_set<int> cycle;

bool bfs()
{
    vector<bool> visited(MAX, false);

    for (auto& vertex : cycle)
    {
        if (visited[vertex] == true)
            continue;

        queue<int> myQ;

        myQ.push(vertex);

        visited[vertex] = true;

        while (myQ.empty() == false)
        {
            auto src = myQ.front();
            myQ.pop();

            for (auto& dst : edgeMatrix[src])
            {
                if (visited[dst] == false)
                {
                    myQ.push(dst);
                    visited[dst] = true;
                }
            }
        }

        if (visited[goal] == true)
            return true;
    }

    return false;
}

void bellmanford()
{
    dist[start] = moneyToEarn[start];

    for (int i{ 0 }; i < N - 1; ++i)
    {
        for (auto& edge : edges)
        {
            auto src{ get<0>(edge) };
            auto dst{ get<1>(edge) };
            auto w{ get<2>(edge) };

            if (dist[src] == -INF)
                continue;

            if (dist[dst] < dist[src] - w + moneyToEarn[dst])
            {
                dist[dst] = dist[src] - w + moneyToEarn[dst];
            }
        }
    }

    bool cycled{ false };

    for (auto& edge : edges)
    {
        auto src{ get<0>(edge) };
        auto dst{ get<1>(edge) };
        auto w{ get<2>(edge) };

        if (dist[src] == -INF)
            continue;

        if (dist[dst] < dist[src] - w + moneyToEarn[dst])
        {
            cycled = true;

            dist[dst] = dist[src] - w + moneyToEarn[dst];

            //dst까지 사이클에 넣으면 안된다. 사이클의 시발점만을 넣어야 한다.
            //dst를 넣으면 사이클과 관련 없는 정점까지 들어가버린다.
            if (cycle.find(src) == cycle.end())
            {
                cycle.insert(src);
            }
        }
    }

    if (dist[goal] == -INF)
    {
        cout << "gg";
        return;
    }

    if (cycled)
    {
        if (bfs())
        {
            cout << "Gee";
            return;
        }
    }

    cout << dist[goal];
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> start >> goal >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };
        cin >> src >> dst >> w;

        edges.push_back({ src,dst,w });

        edgeMatrix[src].push_back(dst);
    }

    for (int i{ 0 }; i < N; ++i)
    {
        int input{ 0 };
        cin >> input;

        moneyToEarn.push_back(input);
    }

    bellmanford();

    return 0;
}