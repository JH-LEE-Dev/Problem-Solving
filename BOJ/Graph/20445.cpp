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
using ll = long long;

#define MAX 201
#define endl '\n'
#define INF numeric_limits<ll>::max()/2

int N{ 0 }, M{ 0 };
vector<vector<ll>> dist(MAX, vector<ll>(MAX, INF));
vector<int> vertexes;
vector<pair<int, int>> ranges;

void input()
{
    cin >> N >> M;

    for (int i{ 0 }; i < N; ++i)
    {
        int src{ 0 }, dst{ 0 };
        cin >> src >> dst;
        ranges.push_back({ src,dst });

        vertexes.push_back(src);
        vertexes.push_back(dst);
    }
}

void floydWarshall()
{
    sort(vertexes.begin(), vertexes.end());

    vertexes.erase(unique(vertexes.begin(), vertexes.end()), vertexes.end());

    int vSize{ (int)vertexes.size() };

    for (int i{ 0 }; i < N; ++i)
    {
        int left{ (int)distance(vertexes.begin(),lower_bound(vertexes.begin(),vertexes.end(),ranges[i].first)) };
        int right{ (int)distance(vertexes.begin(),lower_bound(vertexes.begin(),vertexes.end(),ranges[i].second)) };

        dist[left][right] = ranges[i].second - ranges[i].first + 1;

        for (int j{ left }; j <= right; ++j)
        {
            for (int k{ j }; k <= right; ++k)
            {
                dist[j][k] = min(dist[j][k], dist[left][right]);
            }
        }
    }

    for (int middle{ 0 }; middle < vSize; ++middle)
    {
        for (int left{ 0 }; left < vSize; ++left)
        {
            for (int right{ 0 }; right < vSize; ++right)
            {
                dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
            }
        }
    }
}

void solve()
{
    floydWarshall();

    for (int i = 0; i < M; i++)
    {
        int src{ 0 }, dst{ 0 };
        cin >> src >> dst;

        src = distance(vertexes.begin(), upper_bound(vertexes.begin(), vertexes.end(), src)) - 1;
        dst = distance(vertexes.begin(), lower_bound(vertexes.begin(), vertexes.end(), dst));

        if (src == -1 || dst == vertexes.size() || dist[src][dst] == INF)
            cout << -1 << endl;
        else
            cout << dist[src][dst] << endl;
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