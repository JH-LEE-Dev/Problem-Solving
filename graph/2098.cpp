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
#define INF numeric_limits<int>::max()/2
using namespace std;

#define MAX 17
int N{ 0 };
vector<vector<int>> edges(MAX, vector<int>(MAX, -1));
vector<vector<int>> dist(MAX, vector<int>(1 << 17, -1));
int result{ INF };

int dfs(int curVertex, int curBit)
{
    if (curBit == (1 << N) - 1)
    {
        if (edges[curVertex][0] != 0)
            return edges[curVertex][0];
        else
            return INF;
    }

    if (dist[curVertex][curBit] != -1)
        return dist[curVertex][curBit];

    dist[curVertex][curBit] = INF;

    for (int i{ 0 }; i < N; ++i)
    {
        if (edges[curVertex][i] != 0)
        {
            if ((curBit & (1 << i)) == (1 << i))
                continue;

            dist[curVertex][curBit] = min(dist[curVertex][curBit], edges[curVertex][i] + dfs(i, curBit | (1 << i)));
        }
    }

    return dist[curVertex][curBit];
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        for (int j{ 0 }; j < N; ++j)
        {
            cin >> edges[i][j];
        }
    }

    cout << dfs(0, 1);

    return 0;
}