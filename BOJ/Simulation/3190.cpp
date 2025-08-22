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

#define MAX 101

vector<vector<bool>> apple(MAX, vector<bool>(MAX, false));
vector<pair<int, char>> orders;

int N{ 0 }, K{ 0 }, M{ 0 };
int result{ 0 };

enum DIR { UP, DOWN, LEFT, RIGHT, DEFAULT };

vector<vector<DIR>> dirTable(MAX, vector<DIR>(MAX, DEFAULT));
pair<int, int> tail{ 1,1 };
pair<int, int> head{ 1,1 };
DIR curDir = RIGHT;

bool moving(int timeLimit)
{
    bool eaten{ false };

    while (true)
    {
        ++result;

        switch (curDir)
        {
        case UP:
            head.first -= 1;

            break;
        case DOWN:
            head.first += 1;

            break;
        case LEFT:
            head.second -= 1;

            break;
        case RIGHT:
            head.second += 1;

            break;
        }

        if (head.first > N || head.first <= 0 || head.second > N || head.second <= 0 || dirTable[head.first][head.second] != DEFAULT)
            return false;

        if (apple[head.first][head.second] == false)
        {
            eaten = false;
        }
        else
        {
            eaten = true;
            apple[head.first][head.second] = false;
        }

        dirTable[head.first][head.second] = curDir;

        if (eaten == false)
        {
            auto oldTail = tail;

            switch (dirTable[tail.first][tail.second])
            {
            case UP:

                tail.first -= 1;

                break;
            case DOWN:

                tail.first += 1;
                break;
            case LEFT:

                tail.second -= 1;
                break;
            case RIGHT:

                tail.second += 1;
                break;
            }

            dirTable[oldTail.first][oldTail.second] = DEFAULT;
        }

        if (result == timeLimit)
            return true;
    }
}

void func()
{
    dirTable[1][1] = RIGHT;

    for (auto& it : orders)
    {
        int timeLimit = it.first;
        char order = it.second;

        if (!moving(timeLimit))
            return;

        switch (curDir)
        {
        case UP:

            if (order == 'D')
            {
                curDir = RIGHT;
            }
            else
            {
                curDir = LEFT;
            }

            break;
        case DOWN:
            if (order == 'D')
            {
                curDir = LEFT;
            }
            else
            {
                curDir = RIGHT;
            }
            break;
        case LEFT:
            if (order == 'D')
            {
                curDir = UP;
            }
            else
            {
                curDir = DOWN;
            }
            break;
        case RIGHT:
            if (order == 'D')
            {
                curDir = DOWN;
            }
            else
            {
                curDir = UP;
            }
            break;
        }

        dirTable[head.first][head.second] = curDir;
    }

    moving(INF);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;
    cin >> K;

    for (int i{ 0 }; i < K; ++i)
    {
        int src{ 0 }, dst{ 0 };
        cin >> src >> dst;

        apple[src][dst] = true;
    }

    cin >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        int time{ 0 };
        char order;
        cin >> time >> order;

        orders.push_back({ time,order });
    }

    func();

    cout << result;

    return 0;
}