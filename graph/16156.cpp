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
#include <string.h>
#include <cmath>
#include <bitset>
#include <iomanip>

using ll = long long;
#define endl '\n'
#define INF numeric_limits<ll>::max()
using namespace std;
using vertex = tuple<ll, int, int, int>;
#define MAX 501

int N{ 0 }, M{ 0 };
int table[MAX][MAX];
int result[MAX];

int dir_row[4]{ 0,0,1,-1 };
int dir_col[4]{ 1,-1,0,0 };
vector<vector<ll>> dist(MAX, vector <ll>(MAX, INF));

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

void dijkstra()
{
    priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

    for (int i{ 0 }; i < N; ++i)
    {
        pq.push({ table[i][M - 1],i,M - 1,i });
        dist[i][M - 1] = table[i][M - 1];
    }

    while (pq.empty() == false)
    {
        auto cur{ pq.top() };
        pq.pop();

        auto row{ get<1>(cur) };
        auto col{ get<2>(cur) };
        auto curDist{ get<0>(cur) };
        auto curRow{ get<3>(cur) };

        if (dist[row][col] < curDist)
            continue;

        if (col == 0)
        {
            ++result[curRow];
        }

        for (int i{ 0 }; i < 4; ++i)
        {
            auto newRow{ row + dir_row[i] };
            auto newCol{ col + dir_col[i] };
            auto newDist{ curDist + table[newRow][newCol] };

            if (isValid(newRow, newCol) == false)
                continue;

            if (dist[newRow][newCol] > newDist)
            {
                dist[newRow][newCol] = newDist;
                pq.push({ newDist,newRow,newCol,curRow });
            }
        }
    }
}

void solve()
{
    dijkstra();

    for (int i{ 0 }; i < N; ++i)
    {
        cout << result[i] << endl;
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