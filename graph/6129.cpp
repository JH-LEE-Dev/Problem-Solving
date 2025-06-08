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
#define MAX 101

int N;
vector<vector<char>> table(MAX, vector<char>(MAX, '.'));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(4, INF)));

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

pair<int, int> start;
pair<int, int> goal;

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == 'A')
			{
				start.first = i;
				start.second = j;
			}

			if (table[i][j] == 'B')
			{
				goal.first = i;
				goal.second = j;
			}
		}
	}
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= N || c < 0 || table[r][c] == 'x')
		return false;
	else
		return true;
}

void bfs()
{
	deque<vertex> dq;
	dq.push_back({ 0,0,start.first,start.second });
	dist[start.first][start.second][0] = 0;
	dist[start.first][start.second][1] = 0;
	dist[start.first][start.second][2] = 0;
	dist[start.first][start.second][3] = 0;

	while (dq.empty() == false)
	{
		auto cur{ dq.front() };
		dq.pop_front();

		auto r{ get<2>(cur) };
		auto c{ get<3>(cur) };
		auto curDist{ get<0>(cur) };
		auto curDir{ get<1>(cur) };

		if (dist[r][c][curDir] < curDist)
			continue;

		if (r == goal.first && c == goal.second)
		{
			cout << curDist;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			if (i == curDir || (r == start.first && c == start.second))
			{
				if (dist[nR][nC][i] > curDist)
				{
					dist[nR][nC][i] = curDist;
					dq.push_front({ curDist,i,nR,nC });
				}
			}
			else
			{
				if (dist[nR][nC][i] > curDist + 1)
				{
					dist[nR][nC][i] = curDist + 1;
					dq.push_back({ curDist + 1,i,nR,nC });
				}
			}
		}
	}
}

void solve()
{
	bfs();
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