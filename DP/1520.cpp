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
#define INF numeric_limits<int>::max()

int N{ 0 }, M{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, 0));

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };
vector<vector<int>> DP(MAX, vector<int>(MAX, -1));

bool isValid(int row, int col)
{
    if (row >= N || row < 0 || col >= M || col < 0)
        return false;
    else
        return true;
}

void input()
{
    cin >> N >> M;

    for (int i{ 0 }; i < N; ++i)
    {
        for (int j{ 0 }; j < M; ++j)
        {
            cin >> table[i][j];
        }
    }
}

int dfs(int row, int col, int h)
{
    if (row == N - 1 && col == M - 1)
        return 1;

    if (DP[row][col] != -1)
        return DP[row][col];

    if (DP[row][col] == -1)
        DP[row][col] = 0;

    for (int i{ 0 }; i < 4; ++i)
    {
        int newR{ row + dir_row[i] };
        int newC{ col + dir_col[i] };

        if (isValid(newR, newC) == false)
            continue;

        if (table[newR][newC] < h)
        {
            DP[row][col] += dfs(newR, newC, table[newR][newC]);
        }
    }

    return DP[row][col];
}

void solve()
{
    cout << dfs(0, 0, table[0][0]);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}