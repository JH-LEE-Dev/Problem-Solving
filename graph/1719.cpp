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
#define INF numeric_limits<int>::max()/2
#define MAX 201

int N{ 0 }, M{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<vector<int>> parent(MAX, vector<int>(MAX, -1));

void input()
{
    cin >> N >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };

        cin >> src >> dst >> w;

        dist[src][dst] = w;
        dist[dst][src] = w;
        parent[src][dst] = src;
        parent[dst][src] = dst;
    }

    for (int i{ 1 }; i <= N; ++i)
    {
        dist[i][i] = 0;
    }
}

void floydWarshall()
{
    for (int middle{ 1 }; middle <= N; ++middle)
    {
        for (int left{ 1 }; left <= N; ++left)
        {
            for (int right{ 1 }; right <= N; ++right)
            {
                if (dist[left][right] > dist[left][middle] + dist[middle][right])
                {
                    dist[left][right] = dist[left][middle] + dist[middle][right];
                    parent[left][right] = parent[middle][right];
                }
            }
        }
    }
}

void solve()
{
    floydWarshall();

    for (int i{ 1 }; i <= N; ++i)
    {
        for (int j{ 1 }; j <= N; ++j)
        {
            if (i == j)
            {
                cout << '-' << ' ';
                continue;
            }

            auto cursor{ j };
            while (true)
            {
                if (parent[i][cursor] == i)
                {
                    if (j == N)
                        cout << cursor << endl;
                    else
                        cout << cursor << ' ';

                    break;
                }

                cursor = parent[i][cursor];
            }
        }
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