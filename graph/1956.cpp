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

#define endl '\n'
#define MAX 405
#define INF numeric_limits<int>::max()
using namespace std;

int V{ 0 }, E{ 0 };
vector<vector<long long>> edges(MAX, vector<long long>(MAX, INF));
vector<vector<long long>> dist(MAX, vector<long long>(MAX, INF));

bool cycleFound{ false };
long long result{ INF };

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> V >> E;

    for (int i{ 0 }; i < E; ++i)
    {
        long long src{ 0 }, dst{ 0 }, w;
        cin >> src >> dst >> w;

        edges[src][dst] = w;
    }

    for (int i{ 1 }; i <= V; ++i)
    {
        for (int j{ 1 }; j <= V; ++j)
        {
            dist[i][j] = edges[i][j];
        }

        dist[i][i] = 0;
    }

    for (int mid{ 1 }; mid <= V; ++mid)
    {
        for (int left{ 1 }; left <= V; ++left)
        {
            for (int right{ 1 }; right <= V; ++right)
            {
                if (left == right && mid != left && right != mid)
                {
                    if (dist[left][mid] != INF && dist[mid][right] != INF)
                        result = min(result, dist[left][mid] + dist[mid][right]);
                }

                if (dist[left][mid] + dist[mid][right] < dist[left][right])
                {
                    dist[left][right] = dist[left][mid] + dist[mid][right];
                }
            }
        }
    }

    if (result != INF)
    {
        cout << result;
    }
    else
    {
        cout << -1;
    }

    return 0;
}