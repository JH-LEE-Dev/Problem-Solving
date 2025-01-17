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

#define MAX 401
int N{ 0 }, M{ 0 }, S{ 0 };
vector<pair<int, int>> query;
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

void input()
{
    cin >> N >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 };
        cin >> src >> dst;

        dist[src][dst] = 1;
    }

    cin >> S;

    for (int i{ 0 }; i < S; ++i)
    {
        pair<int, int> temp;
        cin >> temp.first >> temp.second;

        query.push_back(temp);
    }

    for (int i{ 1 }; i < N; ++i)
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
                }
            }
        }
    }
}

void solve()
{
    floydWarshall();

    for (int i{ 0 }; i < S; ++i)
    {
        auto& temp{ query[i] };

        if (dist[temp.first][temp.second] == INF && dist[temp.second][temp.first] == INF)
            cout << 0 << endl;
        else if (dist[temp.first][temp.second] != INF)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << 1 << endl;
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