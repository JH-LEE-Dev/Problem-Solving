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

/*
*	문제 분석
*	1. 위, 아래, 왼쪽, 오른쪽으로 기울이기 동작이 있다.
*	2. 빨간 구슬보다 파란 구슬이 먼저 빠지거나, 동시에 빠진다면 실패.
*	3. 모든 구슬이 더 이상 움직이지 않을 때는 기울이기 동작을 실행하지 않는다.
*	4. 10번 안에 빨간 구슬을 뺄 수 없다면 실패.
*
*	문제 해결 전략
*	1. 기울이는 방식을 dfs로 모든 경우의 수를 탐색한다. 단, 모든 구슬이 더 이상 움직이지 않거나 10번을 넘겼을 때는 실패.
	   만약 빨간 구슬이 먼저 빠지는 경우가 생긴다면, dfs 거리를 비교하여 최소값을 갱신.
	2. 기울이는 동작
	   왼쪽으로 기울일 때는, 가장 왼쪽 구슬부터 이동시킨다. 각 방향 모두 마찬가지.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 11

int N, M;
vector<vector<char>> table(MAX, vector<char>(MAX));

// 오른,왼,아래,위
vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

enum DIR { RIGHT, LEFT, DOWN, UP };

int result{ INF };

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

bool isValid(int r, int c, vector<vector<char>>& _table)
{
	if (r >= N || r < 0 || c >= M || c < 0 || _table[r][c] != '.')
		return false;
	else
		return true;
}

void moveBalls(DIR dir, vector<vector<char>>& _table, bool& redOut, bool& blueOut, bool& ballMove)
{
	switch (dir)
	{
	case UP:
	{
		for (int i{ 0 }; i < N; ++i)
		{
			for (int j{ 0 }; j < M; ++j)
			{
				if (_table[i][j] == 'R' || _table[i][j] == 'B')
				{
					pair<int, int> newCoord{ i,j };

					while (true)
					{
						newCoord.first += dir_row[UP];
						newCoord.second += dir_col[UP];

						if (_table[newCoord.first][newCoord.second] == 'O')
						{
							ballMove = true;

							if (_table[i][j] == 'R')
							{
								redOut = true;
								_table[i][j] = '.';
								break;
							}
							else
							{
								blueOut = true;
								_table[i][j] = '.';
								break;
							}
						}

						if (isValid(newCoord.first, newCoord.second, _table) == false)
						{
							newCoord.first -= dir_row[UP];
							newCoord.second -= dir_col[UP];

							if (newCoord.first == i && newCoord.second == j)
								break;

							_table[newCoord.first][newCoord.second] = _table[i][j];
							_table[i][j] = '.';

							ballMove = true;

							break;
						}
					}
				}
			}
		}
		break;
	}
	case DOWN:
	{
		for (int i{ N - 1 }; i >= 0; --i)
		{
			for (int j{ 0 }; j < M; ++j)
			{
				if (_table[i][j] == 'R' || _table[i][j] == 'B')
				{
					pair<int, int> newCoord{ i,j };

					while (true)
					{
						newCoord.first += dir_row[DOWN];
						newCoord.second += dir_col[DOWN];

						if (_table[newCoord.first][newCoord.second] == 'O')
						{
							ballMove = true;

							if (_table[i][j] == 'R')
							{
								redOut = true;
								_table[i][j] = '.';
								break;
							}
							else
							{
								blueOut = true;
								_table[i][j] = '.';
								break;
							}
						}

						if (isValid(newCoord.first, newCoord.second, _table) == false)
						{
							newCoord.first -= dir_row[DOWN];
							newCoord.second -= dir_col[DOWN];

							if (newCoord.first == i && newCoord.second == j)
								break;

							_table[newCoord.first][newCoord.second] = _table[i][j];
							_table[i][j] = '.';

							ballMove = true;

							break;
						}
					}
				}
			}
		}
		break;
	}
	case LEFT:
	{
		for (int i{ 0 }; i < N; ++i)
		{
			for (int j{ 0 }; j < M; ++j)
			{
				if (_table[i][j] == 'R' || _table[i][j] == 'B')
				{
					pair<int, int> newCoord{ i,j };

					while (true)
					{
						newCoord.first += dir_row[LEFT];
						newCoord.second += dir_col[LEFT];

						if (_table[newCoord.first][newCoord.second] == 'O')
						{
							ballMove = true;

							if (_table[i][j] == 'R')
							{
								redOut = true;
								_table[i][j] = '.';

								break;
							}
							else
							{
								blueOut = true;
								_table[i][j] = '.';

								break;
							}
						}

						if (isValid(newCoord.first, newCoord.second, _table) == false)
						{
							newCoord.first -= dir_row[LEFT];
							newCoord.second -= dir_col[LEFT];

							if (newCoord.first == i && newCoord.second == j)
								break;

							_table[newCoord.first][newCoord.second] = _table[i][j];
							_table[i][j] = '.';

							ballMove = true;

							break;
						}
					}
				}
			}
		}
		break;
	}
	case RIGHT:
	{
		for (int i{ 0 }; i < N; ++i)
		{
			for (int j{ M - 1 }; j >= 0; --j)
			{
				if (_table[i][j] == 'R' || _table[i][j] == 'B')
				{
					pair<int, int> newCoord{ i,j };

					while (true)
					{
						newCoord.first += dir_row[RIGHT];
						newCoord.second += dir_col[RIGHT];

						if (_table[newCoord.first][newCoord.second] == 'O')
						{
							ballMove = true;

							if (_table[i][j] == 'R')
							{
								redOut = true;
								_table[i][j] = '.';
								break;
							}
							else
							{
								blueOut = true;
								_table[i][j] = '.';
								break;
							}
						}

						if (isValid(newCoord.first, newCoord.second, _table) == false)
						{
							newCoord.first -= dir_row[RIGHT];
							newCoord.second -= dir_col[RIGHT];

							if (newCoord.first == i && newCoord.second == j)
								break;

							_table[newCoord.first][newCoord.second] = _table[i][j];
							_table[i][j] = '.';

							ballMove = true;

							break;
						}
					}
				}
			}
		}
		break;
	}
	}
}

void dfs(int dist, DIR dir, vector<vector<char>> _table)
{
	bool redOut{ false }, blueOut{ false }, ballMove{ false };
	moveBalls(dir, _table, redOut, blueOut, ballMove);

	if (dist > 10)
		return;

	if (ballMove == false)
		return;

	if (redOut == true && blueOut == false)
	{
		result = min(result, dist);

		return;
	}
	else if (redOut == true && blueOut == true)
	{
		return;
	}
	else if (redOut == false && blueOut == true)
	{
		return;
	}

	for (int i{ 0 }; i < 4; ++i)
	{
		dfs(dist + 1, (DIR)i, _table);
	}
}

void solve()
{
	for (int i{ 0 }; i < 4; ++i)
	{
		dfs(1, (DIR)i, table);
	}

	if (result == INF)
		cout << -1;
	else
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