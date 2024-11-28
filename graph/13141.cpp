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
#include <iomanip>

#define endl '\n'
#define INF numeric_limits<int>::max()/2
#define INF_FLOAT numeric_limits<float>::max()
using namespace std;

#define MAX 201
int N{ 0 }, M{ 0 };
vector<vector<int>> edges(MAX, vector<int>(MAX, INF));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<vector<pair<int, int>>> adjList(MAX, vector<pair<int, int>>());
float minTime{ INF_FLOAT };

void floydWarshall()
{
    for (int i{ 1 }; i <= N; ++i)
    {
        for (int j{ 1 }; j <= N; ++j)
        {
            dist[i][j] = min(edges[i][j], dist[i][j]);
        }

        dist[i][i] = 0;
    }

    for (int middle{ 1 }; middle <= N; ++middle)
    {
        for (int left{ 1 }; left <= N; ++left)
        {
            for (int right{ 1 }; right <= N; ++right)
            {
                if (dist[left][right] > dist[left][middle] + dist[middle][right])
                    dist[left][right] = dist[left][middle] + dist[middle][right];
            }
        }
    }
}

void bruteforce()
{
    for (int i{ 1 }; i <= N; ++i)
    {
        float timeCost{ -INF_FLOAT };

        for (int j{ 1 }; j <= N; ++j)
        {
            if (dist[i][j] == INF)
                continue;

            for (auto& edge : adjList[j])
            {
                int dst = edge.first;
                int weight = edge.second;

                auto timeDelta = abs(dist[i][dst] - dist[i][j]);

                timeCost = max(timeCost, (float)dist[i][j] + (float)abs(timeDelta - weight) / 2.f);
            }
        }

        minTime = min(minTime, timeCost);
    }
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

        edges[src][dst] = min(edges[src][dst], w);
        edges[dst][src] = min(edges[dst][src], w);

        adjList[src].push_back({ dst,w });
        adjList[dst].push_back({ src,w });
    }

    floydWarshall();
    bruteforce();

    cout << fixed << setprecision(1) << minTime << endl;

    return 0;
}