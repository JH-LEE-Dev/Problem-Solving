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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

// 1 == 'X'
// 2 == 'O'
enum TEAM { X, O };
enum TYPE { ROW, COL };
enum DIA_TYPE { FOR, REV };
vector<vector<int>> table(4, vector<int>(4, 0));
vector<vector<vector<int>>> counting_RowCol(2, vector<vector<int>>(2, vector<int>(4, 0)));
vector<vector<int>> counting_dia(2, vector<int>(2, 0));

bool targetTurn{ false };

void countingFunc(int row, int col, bool turn, bool dir)
{
    if (dir == true)
    {
        ++counting_RowCol[turn][ROW][row];
        ++counting_RowCol[turn][COL][col];

        if (row == col)
        {
            ++counting_dia[turn][FOR];
        }

        if (row + col == 2)
        {
            ++counting_dia[turn][REV];
        }
    }
    else
    {
        --counting_RowCol[turn][ROW][row];
        --counting_RowCol[turn][COL][col];

        if (row == col)
        {
            --counting_dia[turn][FOR];
        }

        if (row + col == 2)
        {
            --counting_dia[turn][REV];
        }
    }
}

bool isFinished(bool turn)
{
    for (int i{ 0 }; i < 2; ++i)
    {
        for (int j{ 0 }; j < 3; ++j)
        {
            if (counting_RowCol[turn][i][j] == 3)
                return true;
        }
    }

    for (int i{ 0 }; i < 2; ++i)
    {
        if (counting_dia[turn][i] == 3)
            return true;
    }

    return false;
}

int backtracking(bool turn)
{
    int minVal{ INF };

    if (isFinished(!turn))
        return -1;

    for (int i{ 0 }; i < 3; ++i)
    {
        for (int j{ 0 }; j < 3; ++j)
        {
            if (table[i][j] == 0)
            {
                if (turn == false)
                    table[i][j] = 1;
                else
                    table[i][j] = 2;

                countingFunc(i, j, turn, true);
                minVal = min(minVal, backtracking(!turn));
                countingFunc(i, j, turn, false);

                table[i][j] = 0;
            }
        }
    }

    if (minVal == INF)
    {
        return 0;
    }

    return -minVal;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int x_count{ 0 }, o_count{ 0 };

    for (int i{ 0 }; i < 3; ++i)
    {
        for (int j{ 0 }; j < 3; ++j)
        {
            cin >> table[i][j];

            if (table[i][j] == 1)
            {
                ++x_count;

                countingFunc(i, j, false, true);
            }
            else if (table[i][j] == 2)
            {
                ++o_count;

                countingFunc(i, j, true, true);
            }
        }
    }

    if (x_count == o_count)
    {
        targetTurn = false;
    }
    else
    {
        targetTurn = true;
    }

    auto result = backtracking(targetTurn);

    if (result == 1)
    {
        cout << 'W';
    }
    else if (result == 0)
    {
        cout << 'D';
    }
    else
    {
        cout << 'L';
    }

    return 0;
}