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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 51

bool line[MAX][MAX] = { false };
pair<int, int> start;
pair<int, int> goal;
int N{ 0 }, K{ 0 }, M{ 0 };
int dist[MAX][MAX] = { INF };

//RIGHT,LEFT,DOWN,UP
int dir_x[4] = { 0,0,1,-1 };
int dir_y[4] = { 1,-1,0,0 };

enum DIR { DEFAULT, UP, DOWN, LEFT, RIGHT };
DIR parent[MAX][MAX] = { DEFAULT };
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> myPQ;
stack<pair<int, int>> path;

bool isValid(int row, int col)
{
    if (row > N || row<1 || col>N || col < 1)
        return false;
    else
        return true;
}

void dijkstra()
{
    if (line[start.first][start.second] == true)
    {
        myPQ.push({ K,start });
        dist[start.first][start.second] = K;
    }
    else
    {
        myPQ.push({ 1,start });
        dist[start.first][start.second] = 1;
    }

    while (myPQ.empty() == false)
    {
        auto cur = myPQ.top();
        myPQ.pop();

        auto src = cur.second;
        auto row_src = src.first;
        auto col_src = src.second;
        auto curDist = cur.first;

        if (row_src == goal.first && col_src == goal.second)
            break;

        if (dist[row_src][col_src] < curDist)
            continue;

        for (int i{ 0 }; i < 4; ++i)
        {
            auto newRow = row_src + dir_x[i];
            auto newCol = col_src + dir_y[i];
            int w = 1;

            if (isValid(newRow, newCol) == false)
            {
                continue;
            }

            if (line[newRow][newCol] == true)
            {
                w = K;
            }

            if (dist[newRow][newCol] > curDist + w)
            {
                dist[newRow][newCol] = curDist + w;
                myPQ.push({ dist[newRow][newCol],{newRow,newCol} });

                switch (i)
                {
                case 0:
                    parent[newRow][newCol] = RIGHT;
                    break;
                case 1:
                    parent[newRow][newCol] = LEFT;
                    break;
                case 2:
                    parent[newRow][newCol] = DOWN;
                    break;
                case 3:
                    parent[newRow][newCol] = UP;
                    break;
                }
            }
        }
    }

    path.push(goal);
    auto curDir = parent[goal.first][goal.second];
    auto curCoord = goal;

    while (curDir != DEFAULT)
    {
        switch (curDir)
        {
        case LEFT:
            curCoord.second += 1;
            break;
        case RIGHT:
            curCoord.second -= 1;
            break;
        case UP:
            curCoord.first += 1;
            break;
        case DOWN:
            curCoord.first -= 1;
            break;
        }

        if (curDir != parent[curCoord.first][curCoord.second] && parent[curCoord.first][curCoord.second] != DEFAULT)
        {
            path.push(curCoord);
        }

        curDir = parent[curCoord.first][curCoord.second];
    }

    path.push(start);

    cout << dist[goal.first][goal.second] << endl;
    cout << path.size() << " ";
    while (path.empty() == false)
    {
        auto cur = path.top();

        cout << cur.first << " " << cur.second << " ";
        path.pop();
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i{ 0 }; i < MAX; ++i)
    {
        for (int j{ 0 }; j < MAX; ++j)
        {
            dist[i][j] = INF;
            line[i][j] = false;
        }
    }

    cin >> N;
    cin >> start.first >> start.second >> goal.first >> goal.second;
    cin >> K;
    cin >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        int counting{ 0 };
        cin >> counting;

        int row_src{ 0 }, col_src{ 0 };
        cin >> row_src >> col_src;

        for (int j{ 0 }; j < counting - 1; ++j)
        {
            int row_dst{ 0 }, col_dst{ 0 };
            cin >> row_dst >> col_dst;

            int rowDelta{ abs(row_src - row_dst) };
            int colDelta{ abs(col_src - col_dst) };

            if (rowDelta != 0)
            {
                if (row_src > row_dst)
                {
                    for (int k{ row_src }; k >= row_dst; --k)
                    {
                        line[k][col_dst] = true;
                    }
                }
                else
                {
                    for (int k{ row_src }; k <= row_dst; ++k)
                    {
                        line[k][col_dst] = true;
                    }
                }
            }
            else
            {
                if (col_src > col_dst)
                {
                    for (int k{ col_src }; k >= col_dst; --k)
                    {
                        line[row_dst][k] = true;
                    }
                }
                else
                {
                    for (int k{ col_src }; k <= col_dst; ++k)
                    {
                        line[row_dst][k] = true;
                    }
                }
            }

            row_src = row_dst;
            col_src = col_dst;
        }
    }

    dijkstra();

    return 0;
}