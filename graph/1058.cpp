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

void input()
{
    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        string str;

        cin >> str;

        for (int j{ 0 }; j < N; ++j)
        {
            if (str[j] == 'Y')
            {
                dist[i][j] = 1;
            }
        }
    }
}

void floydWarshall()
{
    for (int i{ 0 }; i < N; ++i)
    {
        dist[i][i] = 0;
    }

    for (int middle{ 0 }; middle < N; ++middle)
    {
        for (int left{ 0 }; left < N; ++left)
        {
            for (int right{ 0 }; right < N; ++right)
            {
                dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
            }
        }
    }
}

void solve()
{
    floydWarshall();

    int result{ 0 };

    for (int i{ 0 }; i < N; ++i)
    {
        int maxF{ 0 };

        for (int j{ 0 }; j < N; ++j)
        {
            if (dist[i][j] <= 2 && i != j)
                ++maxF;
        }

        result = max(maxF, result);
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