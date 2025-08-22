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

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int T{ 0 };
int N{ 0 }, K{ 0 }, goal{ 0 };

vector<vector<int>> edges(MAX, vector<int>());
vector<int> indegree;
vector<int> buildings;

void input()
{
    cin >> T;
}

int bfs()
{
    queue<int> q;
    vector<int> dist(MAX, -1);

    for (int i{ 1 }; i <= N; ++i)
    {
        if (indegree[i] == 0)
        {
            dist[i] = buildings[i];
            q.push(i);
        }
    }

    while (q.empty() == false)
    {
        auto src{ q.front() };
        q.pop();

        for (auto& dst : edges[src])
        {
            --indegree[dst];
            dist[dst] = max(dist[dst], dist[src] + buildings[dst]);

            if (indegree[dst] == 0)
            {
                if (dst == goal)
                    return dist[dst];

                q.push(dst);
            }
        }
    }

    return dist[goal];
}

void solve()
{
    while (T != 0)
    {
        buildings = vector<int>(MAX, 0);
        indegree = vector<int>(MAX, 0);
        edges = vector<vector<int>>(MAX, vector<int>());

        cin >> N >> K;

        for (int i{ 1 }; i <= N; ++i)
        {
            int input{ 0 };
            cin >> input;

            buildings[i] = input;
        }

        for (int i{ 0 }; i < K; ++i)
        {
            int src{ 0 }, dst{ 0 };

            cin >> src >> dst;

            edges[src].push_back(dst);
            ++indegree[dst];
        }

        cin >> goal;

        auto result{ bfs() };

        cout << result << endl;

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