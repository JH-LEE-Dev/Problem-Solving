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

#define endl '\n'
#define INF 0x3f3f3f3f
using namespace std;

#define MAX 1'001

int N{ 0 }, M{ 0 };
int dist[MAX][MAX][2];
int table[MAX][MAX];

using vertex = tuple<int, int, bool>;

int dir_row[4]{ 0,0,1,-1 };
int dir_col[4]{ 1,-1,0,0 };

bool isValid(int row, int col)
{
    if (row >= N || row < 0 || col >= M || col < 0)
        return false;
    else
        return true;
}

void bfs()
{
    queue<vertex> q;
    q.push({ 0,0,false });
    dist[0][0][false] = 1;

    while (q.empty() == false)
    {
        auto cur{ q.front() };
        q.pop();

        auto row{ get<0>(cur) };
        auto col{ get<1>(cur) };
        auto curBreak{ get<2>(cur) };

        for (int i{ 0 }; i < 4; ++i)
        {
            auto nRow{ row + dir_row[i] };
            auto nCol{ col + dir_col[i] };
            auto newDist{ dist[row][col][curBreak] + 1 };

            if (isValid(nRow, nCol) == false)
                continue;

            if (table[nRow][nCol] == 1)
            {
                if (curBreak == false)
                {
                    if (dist[nRow][nCol][true] > newDist)
                    {
                        q.push({ nRow,nCol,true });
                        dist[nRow][nCol][true] = newDist;
                    }
                }
            }
            else
            {
                if (dist[nRow][nCol][curBreak] > newDist)
                {
                    q.push({ nRow,nCol,curBreak });
                    dist[nRow][nCol][curBreak] = newDist;
                }
            }
        }
    }
}

void input()
{
    cin >> N >> M;

    for (int i{ 0 }; i < N; ++i)
    {
        string temp;
        cin >> temp;

        for (int j{ 0 }; j < M; ++j)
        {
            table[i][j] = temp[j] - '0';
        }
    }
}

void init()
{
    memset(dist, INF, sizeof(dist));
}

void solve()
{
    bfs();

    auto result{ min(dist[N - 1][M - 1][true],dist[N - 1][M - 1][false]) };

    if (result == INF)
        cout << -1;
    else
        cout << result;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();
    input();
    solve();

    return 0;
}