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
#include <deque>

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;
#define MAX 105
vector<pair<int, int>> prisoners;
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(3, -1)));
vector<vector<char>> jail(MAX, vector<char>(MAX, '.'));

int T{ 0 };
int H{ 0 }, W{ 0 };

vector<int> dir_x{ 0,0,1,-1 };
vector<int> dir_y{ 1,-1,0,0 };

int result{ INF };

bool isValid(pair<int, int> coord)
{
    auto x = coord.first;
    auto y = coord.second;

    if (x < 0 || x > H + 1 || y < 0 || y > W + 1)
        return false;

    if (jail[x][y] == '*')
        return false;

    return true;
}

bool isDoor(pair<int, int> coord)
{
    return jail[coord.first][coord.second] == '#';
}

void bfs()
{
    for (int i{ 0 }; i < 3; ++i)
    {
        deque<tuple<int, int>> myQ;

        if (i == 0)
        {
            dist[0][0][0] = 0;
            myQ.push_back({ 0,0 });
        }
        else
        {
            dist[prisoners[i - 1].first][prisoners[i - 1].second][i] = 0;
            myQ.push_back({ prisoners[i - 1].first,prisoners[i - 1].second });
        }

        while (myQ.empty() == false)
        {
            auto cur = myQ.front();
            myQ.pop_front();

            auto curX = get<0>(cur);
            auto curY = get<1>(cur);

            for (int j{ 0 }; j < 4; ++j)
            {
                auto newX = curX + dir_x[j];
                auto newY = curY + dir_y[j];

                if (isValid({ newX,newY }) == false)
                    continue;

                if (isDoor({ newX,newY }))
                {
                    if (dist[newX][newY][i] == -1)
                    {
                        dist[newX][newY][i] = dist[curX][curY][i] + 1;
                        myQ.push_back({ newX,newY });
                    }
                }
                else
                {
                    if (dist[newX][newY][i] == -1)
                    {
                        dist[newX][newY][i] = dist[curX][curY][i];
                        myQ.push_front({ newX,newY });
                    }
                }
            }
        }
    }

    for (int i{ 0 }; i <= H + 1; ++i)
    {
        for (int j{ 0 }; j <= W + 1; ++j)
        {
            if (jail[i][j] == '*' || dist[i][j][0] == -1 || dist[i][j][1] == -1 || dist[i][j][2] == -1)
                continue;

            int total = dist[i][j][0] + dist[i][j][1] + dist[i][j][2];

            if (jail[i][j] == '#')
                total -= 2;

            result = min(total, result);
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> T;

    while (T != 0)
    {
        cin >> H >> W;

        jail = vector<vector<char>>(MAX, vector<char>(MAX, '.'));
        dist = vector<vector<vector<int>>>(MAX, vector<vector<int>>(MAX, vector<int>(3, -1)));
        prisoners.clear();
        result = INF;

        for (int i{ 1 }; i <= H; ++i)
        {
            for (int j{ 1 }; j <= W; ++j)
            {
                cin >> jail[i][j];

                if (jail[i][j] == '$')
                    prisoners.push_back({ i,j });
            }
        }

        bfs();

        --T;

        cout << result << endl;
    }

    return 0;
}