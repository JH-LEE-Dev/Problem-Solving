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
using vertex = tuple<int, int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 501

enum TYPE { LEFT, RIGHT };

int N{ 0 }, M{ 0 };

vector<vector<TYPE>> table(MAX, vector<TYPE>(MAX));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(2, INF)));

vector<int> dir_LEFT_1{ 1,0,-1,0,1,-1 };
vector<int> dir_LEFT_2{ 0,1,0,-1,1,-1 };
vector<int> dir_RIGHT_1{ -1,0,1,0,-1,1 };
vector<int> dir_RIGHT_2{ 0,1,0,-1,1,-1 };

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= M || col < 0)
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
			char input;
			cin >> input;

			if (input == '\\')
			{
				table[i][j] = LEFT;
			}
			else
			{
				table[i][j] = RIGHT;
			}
		}
	}
}

void bfs()
{
	deque<vertex>dq;

	if (table[0][0] == RIGHT)
	{
		dq.push_back({ 0,0,1,!table[0][0] });
		dist[0][0][!table[0][0]] = 1;
		dist[0][0][table[0][0]] = 0;
	}
	else
	{
		dq.push_front({ 0,0,0,table[0][0] });
		dist[0][0][table[0][0]] = 0;
		dist[0][0][!table[0][0]] = 0;
	}

	while (dq.empty() == false)
	{
		auto cur{ dq.front() };
		dq.pop_front();

		auto row{ get<0>(cur) };
		auto col{ get<1>(cur) };
		auto curDist{ get<2>(cur) };
		auto curType{ get<3>(cur) };

		if (dist[row][col][curType] < curDist)
			continue;

		if (curType == LEFT)
		{
			for (int i{ 0 }; i < 4; ++i)
			{
				auto nR{ row + dir_LEFT_1[i] };
				auto nC{ col + dir_LEFT_2[i] };

				if (isValid(nR, nC) == false)
					continue;

				if (table[nR][nC] == curType)
				{
					if (dist[nR][nC][!curType] > curDist + 1)
					{
						dq.push_back({ nR,nC,curDist + 1,!curType });
						dist[nR][nC][!curType] = curDist + 1;
					}
				}
				else
				{
					if (dist[nR][nC][!curType] > curDist)
					{
						dq.push_front({ nR,nC,curDist,!curType });
						dist[nR][nC][!curType] = curDist;
					}
				}
			}

			for (int i{ 4 }; i < 6; ++i)
			{
				auto nR{ row + dir_LEFT_1[i] };
				auto nC{ col + dir_LEFT_2[i] };

				if (isValid(nR, nC) == false)
					continue;

				if (table[nR][nC] != curType)
				{
					if (dist[nR][nC][curType] > curDist + 1)
					{
						dq.push_back({ nR,nC,curDist + 1,curType });
						dist[nR][nC][curType] = curDist + 1;
					}
				}
				else
				{
					if (dist[nR][nC][curType] > curDist)
					{
						dq.push_front({ nR,nC,curDist,curType });
						dist[nR][nC][curType] = curDist;
					}
				}
			}
		}
		else
		{
			for (int i{ 0 }; i < 4; ++i)
			{
				auto nR{ row + dir_RIGHT_1[i] };
				auto nC{ col + dir_RIGHT_2[i] };

				if (isValid(nR, nC) == false)
					continue;

				if (table[nR][nC] == curType)
				{
					if (dist[nR][nC][!curType] > curDist + 1)
					{
						dq.push_back({ nR,nC,curDist + 1,!curType });
						dist[nR][nC][!curType] = curDist + 1;
					}
				}
				else
				{
					if (dist[nR][nC][!curType] > curDist)
					{
						dq.push_front({ nR,nC,curDist,!curType });
						dist[nR][nC][!curType] = curDist;
					}
				}
			}

			for (int i{ 4 }; i < 6; ++i)
			{
				auto nR{ row + dir_RIGHT_1[i] };
				auto nC{ col + dir_RIGHT_2[i] };

				if (isValid(nR, nC) == false)
					continue;

				if (table[nR][nC] != curType)
				{
					if (dist[nR][nC][curType] > curDist + 1)
					{
						dq.push_back({ nR,nC,curDist + 1,curType });
						dist[nR][nC][curType] = curDist + 1;
					}
				}
				else
				{
					if (dist[nR][nC][curType] > curDist)
					{
						dq.push_front({ nR,nC,curDist,curType });
						dist[nR][nC][curType] = curDist;
					}
				}
			}
		}
	}
}

void solve()
{
	bfs();

	auto result{ dist[N - 1][M - 1][LEFT] };

	if (result == INF)
		cout << "NO SOLUTION";
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