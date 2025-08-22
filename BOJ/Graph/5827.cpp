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
*	문제 해결 전략
*	1. 0-1 BFS를 사용한다. 거리는 2차원이고, 1차원은 중력 반전 횟수, 2차원은 현재 중력 방향이다.
*
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 501

int N, M;
vector<vector<char>> table(MAX, vector<char>(MAX));

pair<int, int> start;
pair<int, int> goal;

int result{ -1 };
bool findGoal{ false };

vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(2, INF)));

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0)
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

			if (table[i][j] == 'C')
			{
				start.first = i;
				start.second = j;
			}

			if (table[i][j] == 'D')
			{
				goal.first = i;
				goal.second = j;
			}
		}
	}
}

void addToDeque(int nR, int nC, int newDist, int curType, bool inversed, deque<tuple<int, int, int, int>>& _dq)
{
	if (isValid(nR, nC) == false || dist[nR][nC][curType] <= newDist)
		return;

	if (table[nR][nC] == '#')
		return;

	if (curType == 0)
	{
		auto downRow{ nR + 1 };

		if (isValid(downRow, nC) == false)
			return;
	}
	else
	{
		auto downRow{ nR - 1 };

		if (isValid(downRow, nC) == false)
			return;
	}

	dist[nR][nC][curType] = newDist;

	if (inversed)
		_dq.push_back({ newDist,curType,nR,nC });
	else
		_dq.push_front({ newDist,curType,nR,nC });
}

bool goWithGravity(int r, int c, int type, int curDist, deque<tuple<int, int, int, int>>& _dq, bool inversed, int& nR, int& nC)
{
	if (type == 0)
	{
		while (true)
		{
			nR += 1;

			if (isValid(nR, nC) == false)
			{
				return false;
			}

			if (table[nR][nC] == '#')
			{
				nR -= 1;

				break;
			}

			if (nR == goal.first && nC == goal.second)
			{
				findGoal = true;

				result = curDist;
				return true;
			}
		}

		if (dist[nR][nC][type] > curDist)
		{
			dist[nR][nC][type] = min(dist[nR][nC][type], curDist);
		}

		nC += 1;

		addToDeque(nR, nC, curDist, type, inversed, _dq);

		nC -= 2;

		addToDeque(nR, nC, curDist, type, inversed, _dq);

		nC += 1;
	}
	else
	{
		while (true)
		{
			nR -= 1;

			if (isValid(nR, nC) == false)
			{
				return false;
			}

			if (table[nR][nC] == '#')
			{
				nR += 1;

				break;
			}

			if (nR == goal.first && nC == goal.second)
			{
				findGoal = true;

				result = curDist;
				return true;
			}
		}

		if (dist[nR][nC][type] > curDist)
		{
			dist[nR][nC][type] = min(dist[nR][nC][type], curDist);
		}

		nC += 1;

		addToDeque(nR, nC, curDist, type, inversed, _dq);

		nC -= 2;

		addToDeque(nR, nC, curDist, type, inversed, _dq);

		nC += 1;
	}

	return true;
}


void bfs()
{
	deque<tuple<int, int, int, int>> dq;
	dq.push_front({ 0,0,start.first,start.second });
	dist[start.first][start.second][0] = 0;

	while (dq.empty() == false)
	{
		auto cur{ dq.front() };
		dq.pop_front();

		auto r{ get<2>(cur) };
		auto c{ get<3>(cur) };
		auto curDist{ get<0>(cur) };
		auto curType{ get<1>(cur) };

		if (dist[r][c][curType] < curDist)
			continue;

		if (r == goal.first && c == goal.second)
		{
			result = curDist;

			return;
		}

		auto nR{ r };
		auto nC{ c };

		if (goWithGravity(r, c, curType, curDist, dq, false, nR, nC))
		{
			if (findGoal)
				return;

			curType = 1 - curType;

			goWithGravity(nR, nC, curType, curDist + 1, dq, true, nR, nC);

			if (findGoal)
				return;
		}
	}
}

void solve()
{
	auto nR{ start.first };
	auto nC{ start.second };

	while (true)
	{
		nR += 1;

		if (isValid(nR, nC) == false)
		{
			cout << -1;
			return;
		}

		if (table[nR][nC] == '#' || table[nR][nC] == 'D')
			break;
	}

	bfs();

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