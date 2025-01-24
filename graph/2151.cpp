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

enum DIR { UP, DOWN, LEFT, RIGHT };
using vertex = tuple<int, int, int, DIR>;

#define MAX 51
#define endl '\n'
#define INF numeric_limits<int>::max()

int N{ 0 };
vector<vector<char>> table(MAX, vector<char>(MAX, '.'));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(4, INF)));

pair<int, int> start{ -1,-1 };
pair<int, int> goal{ -1,-1 };

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= N || col < 0 || table[row][col] == '*')
		return false;
	else
		return true;
}

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == '#')
			{
				if (start.first == -1)
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
	deque<vertex>dq;

	for (int i{ 0 }; i < 4; ++i)
	{
		auto nRow{ start.first + dir_row[i] };
		auto nCol{ start.second + dir_col[i] };

		if (isValid(nRow, nCol) == false)
			continue;

		dist[nRow][nCol][i] = 0;

		dq.push_front({ nRow,nCol,0,(DIR)i });
	}

	while (dq.empty() == false)
	{
		auto cur{ dq.front() };
		dq.pop_front();

		auto row{ get<0>(cur) };
		auto col{ get<1>(cur) };
		auto curCount{ get<2>(cur) };
		auto prevDir{ get<3>(cur) };

		if (dist[row][col][prevDir] < curCount)
			continue;

		if (table[row][col] == '!')
		{
			if ((int)prevDir < 2)
			{
				for (int i{ 2 }; i < 4; ++i)
				{
					auto nR{ row + dir_row[i] };
					auto nC{ col + dir_col[i] };

					if (isValid(nR, nC) == false)
						continue;

					if (dist[nR][nC][i] > curCount + 1)
					{
						dist[nR][nC][i] = curCount + 1;
						dq.push_back({ nR,nC,curCount + 1,(DIR)i });
					}
				}
			}
			else
			{
				for (int i{ 0 }; i < 2; ++i)
				{
					auto nR{ row + dir_row[i] };
					auto nC{ col + dir_col[i] };

					if (isValid(nR, nC) == false)
						continue;

					if (dist[nR][nC][i] > curCount + 1)
					{
						dist[nR][nC][i] = curCount + 1;
						dq.push_back({ nR,nC,curCount + 1,(DIR)i });
					}
				}
			}
		}

		auto nR{ row + dir_row[prevDir] };
		auto nC{ col + dir_col[prevDir] };

		if (isValid(nR, nC) == false)
			continue;

		if (dist[nR][nC][prevDir] > curCount)
		{
			dist[nR][nC][prevDir] = curCount;
			dq.push_front({ nR,nC,curCount,prevDir });
		}
	}
}

void solve()
{
	bfs();

	auto result{ INF };
	for (int i{ 0 }; i < 4; ++i)
	{
		result = min(result, dist[goal.first][goal.second][i]);
	}

	cout << result;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}