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

#define MAX 150

int N{ 0 };
vector<vector<int>> edges(11, vector<int>(11, 0));
vector<vector<vector<vector<pair<int, int>>>>> counting(11, vector<vector<vector<pair<int, int>>>>(11, vector<vector<pair<int, int>>>(3, vector<pair<int, int>>(MAX, { INF,INF }))));
pair<int, int> start;
enum TYPE { KNIGHT, BISHOP, ROOK, DEFAULT };
priority_queue<tuple<int, int, int, pair<int, int>, TYPE>, vector<tuple<int, int, int, pair<int, int>, TYPE>>, greater<tuple<int, int, int, pair<int, int>, TYPE>>> myPQ;

vector<int> knight_dir_x{ -1,-2,-2,-1,1,2,2,1 };
vector<int> knight_dir_y{ -2,-1,1,2,-2 ,-1,1,2 };
pair<int, int> result{ INF,INF };

bool isValid(pair<int, int> coord)
{
    int row{ coord.first };
    int col{ coord.second };

    if (row >= N || row < 0 || col >= N || col < 0)
        return false;
    else
        return true;
}

void knightMove(tuple<int, int, int, pair<int, int>, TYPE>& node, bool isChanged)
{
    auto coord{ get<3>(node) };
    auto type{ get<4>(node) };
    auto curNode{ get<1>(node) };
    auto curDist{ get<0>(node) };
    auto curChange{ get<2>(node) };

    int row{ coord.first };
    int col{ coord.second };

    pair<int, int> curValue{ curDist + 1,curChange };

    if (isChanged)
    {
        curValue.second += 1;

        if (counting[coord.first][coord.second][KNIGHT][curNode] > curValue)
        {
            myPQ.push({ curDist + 1,curNode,curChange + 1 ,coord,KNIGHT });
            counting[coord.first][coord.second][KNIGHT][curNode] = curValue;
        }

        return;
    }

    for (int i{ 0 }; i < 8; ++i)
    {
        int nextX{ row + knight_dir_x[i] };
        int nextY{ col + knight_dir_y[i] };

        if (isValid({ nextX,nextY }))
        {
            auto newNode{ curNode };

            if (edges[nextX][nextY] == curNode + 1)
            {
                newNode += 1;
            }

            if (counting[nextX][nextY][KNIGHT][newNode] > curValue)
            {
                myPQ.push({ curDist + 1,newNode,curChange ,{nextX,nextY},KNIGHT });
                counting[nextX][nextY][KNIGHT][newNode] = curValue;
            }
        }
    }
}

void bishopMove(tuple<int, int, int, pair<int, int>, TYPE>& node, bool isChanged)
{
    auto coord{ get<3>(node) };
    auto type{ get<4>(node) };
    auto curNode{ get<1>(node) };
    auto curDist{ get<0>(node) };
    auto curChange{ get<2>(node) };

    int row{ coord.first };
    int col{ coord.second };

    int nextX{ row }, nextY{ col };
    int dirCount{ 0 };

    pair<int, int> curValue{ curDist + 1,curChange };

    if (isChanged)
    {
        if (counting[coord.first][coord.second][BISHOP][curNode] > curValue)
        {
            myPQ.push({ curDist + 1,curNode,curChange + 1 ,coord,BISHOP });
            counting[coord.first][coord.second][BISHOP][curNode] = curValue;
        }

        return;
    }

    while (true)
    {
        if (dirCount == 4)
            break;

        switch (dirCount)
        {
        case 0:
            nextX -= 1;
            nextY -= 1;

            break;
        case 1:
            nextX += 1;
            nextY -= 1;

            break;
        case 2:
            nextX -= 1;
            nextY += 1;

            break;
        case 3:
            nextX += 1;
            nextY += 1;

            break;
        }

        if (isValid({ nextX,nextY }))
        {
            auto newNode{ curNode };

            if (edges[nextX][nextY] == curNode + 1)
            {
                newNode += 1;
            }

            if (counting[nextX][nextY][BISHOP][newNode] > curValue)
            {
                myPQ.push({ curDist + 1,newNode,curChange ,{nextX,nextY},BISHOP });
                counting[nextX][nextY][BISHOP][newNode] = curValue;
            }
        }
        else
        {
            nextX = row;
            nextY = col;

            ++dirCount;
        }
    }
}

void rookMove(tuple<int, int, int, pair<int, int>, TYPE>& node, bool isChanged)
{
    auto coord{ get<3>(node) };
    auto type{ get<4>(node) };
    auto curNode{ get<1>(node) };
    auto curDist{ get<0>(node) };
    auto curChange{ get<2>(node) };

    int row{ coord.first };
    int col{ coord.second };

    int nextX{ row }, nextY{ col };
    int dirCount{ 0 };

    pair<int, int> curValue{ curDist + 1,curChange };

    if (isChanged)
    {
        curValue.second += 1;

        if (counting[coord.first][coord.second][ROOK][curNode] > curValue)
        {
            myPQ.push({ curDist + 1,curNode,curChange + 1 ,coord,ROOK });
            counting[coord.first][coord.second][ROOK][curNode] = curValue;
        }

        return;
    }

    while (true)
    {
        if (dirCount == 4)
            break;

        switch (dirCount)
        {
        case 0:
            nextX -= 1;

            break;
        case 1:
            nextY -= 1;

            break;
        case 2:
            nextY += 1;

            break;
        case 3:
            nextX += 1;

            break;
        }

        if (isValid({ nextX,nextY }))
        {
            auto newNode{ curNode };

            if (edges[nextX][nextY] == curNode + 1)
            {
                newNode += 1;
            }

            if (counting[nextX][nextY][ROOK][newNode] > curValue)
            {
                myPQ.push({ curDist + 1,newNode,curChange ,{nextX,nextY},ROOK });
                counting[nextX][nextY][ROOK][newNode] = curValue;
            }
        }
        else
        {
            nextX = row;
            nextY = col;

            ++dirCount;
        }
    }
}

void nextMove(tuple<int, int, int, pair<int, int>, TYPE>& node)
{
    auto coord{ get<3>(node) };
    auto type{ get<4>(node) };
    auto curNode{ get<1>(node) };
    auto curDist{ get<0>(node) };
    auto curChange{ get<2>(node) };

    if (curNode == N * N)
    {
        if (result.first > curDist)
        {
            result.first = curDist;
            result.second = curChange;
        }
        else if (result.first == curDist)
        {
            result.second = min(result.second, curChange);
        }

        return;
    }

    switch (type)
    {
    case KNIGHT:
        knightMove(node, false);
        bishopMove(node, true);
        rookMove(node, true);
        break;
    case BISHOP:
        knightMove(node, true);
        bishopMove(node, false);
        rookMove(node, true);
        break;
    case ROOK:
        knightMove(node, true);
        bishopMove(node, true);
        rookMove(node, false);
        break;
    }
}

void dijkstra()
{
    myPQ.push({ 0,1,0,start,KNIGHT });
    myPQ.push({ 0,1,0,start,BISHOP });
    myPQ.push({ 0,1,0,start,ROOK });
    counting[start.first][start.second][KNIGHT][1] = make_pair(0, 0);
    counting[start.first][start.second][BISHOP][1] = make_pair(0, 0);
    counting[start.first][start.second][ROOK][1] = make_pair(0, 0);

    while (myPQ.empty() == false)
    {
        auto cur{ myPQ.top() };
        myPQ.pop();

        nextMove(cur);
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        for (int j{ 0 }; j < N; ++j)
        {
            cin >> edges[i][j];

            if (edges[i][j] == 1)
            {
                start.first = i;
                start.second = j;
            }
        }
    }

    dijkstra();

    cout << result.first << ' ' << result.second;

    return 0;
}