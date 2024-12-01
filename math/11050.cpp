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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

int N{ 0 }, M{ 0 };
vector<vector<int>> DP(11, vector<int>(11, 0));

void func(int n, int m)
{
    for (int i{ 0 }; i <= n; ++i)
    {
        DP[i][0] = 1;
    }

    for (int i{ 1 }; i <= n; ++i)
    {
        for (int j{ 1 }; j <= min(i, m); ++j)
        {
            DP[i][j] = DP[i - 1][j] + DP[i - 1][j - 1];
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;

    func(N, M);
    cout << DP[N][M];

    return 0;
}