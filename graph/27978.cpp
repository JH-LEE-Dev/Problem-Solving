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
*	1. 0-1 BFS를 활용해서 보물까지의 최단 거리를 찾는다.
*/

using namespace std;
using vertex = tuple<int, int, int>;
#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 501

int N, M;
vector<vector<char>> table(MAX, vector<char>(MAX));

pair<int, int> start;
pair<int, int> goal;

vector<int> dir_row{ 1,-1,0,1,-1,-1,1,0 };
vector<int> dir_col{ 1,1,1,0,0,-1,-1,-1 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == 'K')
			{
				start.first = i;
				start.second = j;
			}

			if (table[i][j] == '*')
			{
				goal.first = i;
				goal.second = j;
			}
		}
	}
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0 || table[r][c] == '#')
		return false;
	else
		return true;
}

void bfs()
{
	deque<vertex> dq;
	dq.push_front({ 0,start.first,start.second });
	dist[start.first][start.second] = 0;

	while (dq.empty() == false)
	{
		auto cur{ dq.front() };
		dq.pop_front();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[r][c] < curDist)
			continue;

		for (int i{ 0 }; i < 8; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			int w = 1;

			if (i < 3)
				w = 0;

			auto newDist{ curDist + w };

			if (dist[nR][nC] > newDist)
			{
				if (w == 0)
					dq.push_front({ newDist,nR,nC });
				else
					dq.push_back({ newDist,nR,nC });

				dist[nR][nC] = newDist;
			}
		}
	}
}

void solve()
{
	bfs();

	if (dist[goal.first][goal.second] == INF)
		cout << -1;
	else
		cout << dist[goal.first][goal.second];
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