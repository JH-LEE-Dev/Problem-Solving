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
#define MAX 51

int N{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
int result{ INF };
vector<int> candidate;
vector<int> maxScores(MAX, INF);

void input()
{
    cin >> N;

    while (true)
    {
        int src{ 0 }, dst{ 0 };
        cin >> src >> dst;

        if (src == -1 && dst == -1)
            break;

        dist[src][dst] = 1;
        dist[dst][src] = 1;
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
        int maxScore{ 0 };

        for (int j{ 1 }; j <= N; ++j)
        {
            if (i == j)
                continue;

            maxScore = max(maxScore, dist[i][j]);
        }

        maxScores[i] = maxScore;
        result = min(maxScores[i], result);
    }

    for (int i{ 1 }; i <= N; ++i)
    {
        if (maxScores[i] == result)
            candidate.push_back(i);
    }

    cout << result << " ";
    cout << candidate.size() << endl;

    for (auto& v : candidate)
    {
        cout << v << " ";
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