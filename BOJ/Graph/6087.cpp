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

enum DIR { RIGHT, LEFT, UP, DOWN, DEFAULT };

using namespace std;
using vertex = tuple<int, int, int, DIR>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N{ 0 }, M{ 0 };
vector<vector<char>> table(MAX, vector<char>(MAX));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(4, INF)));

//RIGHT,LEFT,UP,DOWN
vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

pair<int, int> start{ -1, -1 };
pair<int, int> goal{ -1,-1 };

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= M || col < 0 || table[row][col] == '*')
		return false;
	else
		return true;
}

void input()
{
	cin >> N >> M;
	swap(N, M);

	for (int i{ 0 }; i < N; ++i)
	{
		string str;
		cin >> str;

		for (int j{ 0 }; j < str.length(); ++j)
		{
			table[i][j] = str[j];

			if (table[i][j] == 'C')
			{
				if (start.first == -1 && start.second == -1)
				{
					start.first = i;
					start.second = j;
				}
				else
				{
					goal.first = i;
					goal.second = j;
				}
			}
		}
	}
}

void bfs()
{
	deque<vertex> dq;

	//시작점에서는 4방향으로 진행
	for (int i{ 0 }; i < 4; ++i)
	{
		dist[start.first][start.second][i] = 0;

		auto nRow{ start.first + dir_row[i] };
		auto nCol{ start.second + dir_col[i] };

		if (isValid(nRow, nCol) == false)
			continue;

		if (dist[nRow][nCol][(DIR)i] >= 0)
		{
			dist[nRow][nCol][(DIR)i] = 0;
			dq.push_front({ nRow,nCol,0,(DIR)i });
		}
	}

	while (dq.empty() == false)
	{
		auto cur{ dq.front() };
		dq.pop_front();

		auto row{ get<0>(cur) };
		auto col{ get<1>(cur) };
		auto curDist{ get<2>(cur) };
		auto prevDir{ get<3>(cur) };

		if (dist[row][col][prevDir] < curDist)
			continue;

		if (row == goal.first && col == goal.second)
			break;

		auto nRow{ row };
		auto nCol{ col };
		auto sRow_1{ row };
		auto sRow_2{ row };
		auto sCol_1{ col };
		auto sCol_2{ col };

		DIR nextDir_1{ DEFAULT };
		DIR nextDir_2{ DEFAULT };

		//직선 방향
		switch (prevDir)
		{
		case RIGHT:
			nRow += dir_row[0];
			nCol += dir_col[0];

			//양 옆 방향
			sRow_1 += dir_row[2];
			sCol_1 += dir_col[2];
			nextDir_1 = UP;

			sRow_2 += dir_row[3];
			sCol_2 += dir_col[3];
			nextDir_2 = DOWN;
			break;
		case LEFT:
			nRow += dir_row[1];
			nCol += dir_col[1];

			//양 옆 방향
			sRow_1 += dir_row[2];
			sCol_1 += dir_col[2];
			nextDir_1 = UP;

			sRow_2 += dir_row[3];
			sCol_2 += dir_col[3];
			nextDir_2 = DOWN;
			break;
		case UP:
			nRow += dir_row[2];
			nCol += dir_col[2];

			//양 옆 방향
			sRow_1 += dir_row[0];
			sCol_1 += dir_col[0];
			nextDir_1 = RIGHT;

			sRow_2 += dir_row[1];
			sCol_2 += dir_col[1];
			nextDir_2 = LEFT;
			break;
		case DOWN:
			nRow += dir_row[3];
			nCol += dir_col[3];

			//양 옆 방향
			sRow_1 += dir_row[0];
			sCol_1 += dir_col[0];
			nextDir_1 = RIGHT;

			sRow_2 += dir_row[1];
			sCol_2 += dir_col[1];
			nextDir_2 = LEFT;
			break;
		}

		if (isValid(nRow, nCol))
		{
			if (dist[nRow][nCol][prevDir] > curDist)
			{
				dist[nRow][nCol][prevDir] = curDist;
				dq.push_front({ nRow,nCol,curDist,prevDir });
			}
		}

		//양 옆 방향
		if (isValid(sRow_1, sCol_1))
		{
			if (dist[sRow_1][sCol_1][nextDir_1] > curDist + 1)
			{
				dist[sRow_1][sCol_1][nextDir_1] = curDist + 1;
				dq.push_back({ sRow_1,sCol_1,curDist + 1,nextDir_1 });
			}
		}

		if (isValid(sRow_2, sCol_2))
		{
			if (dist[sRow_2][sCol_2][nextDir_2] > curDist + 1)
			{
				dist[sRow_2][sCol_2][nextDir_2] = curDist + 1;
				dq.push_back({ sRow_2,sCol_2,curDist + 1,nextDir_2 });
			}
		}
	}
}

void solve()
{
	bfs();

	int result{ INF };
	for (int i{ 0 }; i < 4; ++i)
	{
		result = min(result, dist[goal.first][goal.second][i]);
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