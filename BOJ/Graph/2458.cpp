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

#define MAX 501
#define endl '\n'
#define INF numeric_limits<int>::max()/2
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

int N{ 0 }, M{ 0 };

void input()
{
    cin >> N >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 };
        cin >> src >> dst;
        dist[src][dst] = 1;
    }
}

void floydWarshall()
{
    for (int i{ 1 }; i <= N; ++i)
    {
        dist[i][i] = 0;
    }

    for (int middle{ 1 }; middle <= N; ++middle)
    {
        for (int right{ 1 }; right <= N; ++right)
        {
            for (int left{ 1 }; left <= N; ++left)
            {
                if (dist[left][right] > dist[left][middle] + dist[middle][right])
                {
                    dist[left][right] = dist[left][middle] + dist[middle][right];
                }
            }
        }
    }
}

void solve()
{
    floydWarshall();

    int result{ 0 };

    for (int i{ 1 }; i <= N; ++i)
    {
        int counting{ 0 };

        for (int j{ 1 }; j <= N; ++j)
        {
            if (i == j)
                continue;

            if (dist[i][j] != INF || dist[j][i] != INF)
                ++counting;
        }

        if (counting == N - 1)
            ++result;
    }

    cout << result;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}