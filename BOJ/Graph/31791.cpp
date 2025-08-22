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
*	1. 다익스트라 알고리즘을 활용하여, 탐색한다.
*	2. 상하 좌우 인접 타일로 이동하는 시간은 1초, 만약 인접 타일이 건물이라면, 감염되는 시간 Tb를 더해서 1+Tb를 거리로 한다.
*	3. 다익스트라 알고리즘에서 dq의 top이 Tg보다 크다면, 전파가 종료된 것이므로 알고리즘을 종료하고 감염되지 않은 타일들을 출력한다.
*	4. 감염되지 않은 타일들은, 거리가 INF이거나 Tg보다 크다.
*/

using namespace std;
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX	1'001

int N, M, Tg, Tb, X, B;
vector<vector<char>> table(MAX, vector<char>(MAX));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

vector<pair<int, int>> virus;
vector<pair<int, int>> buildings;

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

void input()
{
	cin >> N >> M;

	cin >> Tg >> Tb >> X >> B;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == '#')
			{
				buildings.push_back({ i,j });
			}

			if (table[i][j] == '*')
			{
				virus.push_back({ i,j });
			}
		}
	}
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0)
		return false;
	else
		return true;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	for (int i{ 0 }; i < X; ++i)
	{
		dist[virus[i].first][virus[i].second] = 0;
		pq.push({ 0,virus[i].first,virus[i].second });
	}

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[r][c] < curDist)
			continue;

		if (curDist > Tg)
			return;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };
			auto newDist{ curDist + 1 };

			if (isValid(nR, nC) == false)
				continue;

			if (table[nR][nC] == '#')
			{
				newDist += Tb;

				if (dist[nR][nC] > newDist)
				{
					pq.push({ newDist,nR,nC });
					dist[nR][nC] = newDist;
				}
			}
			else
			{
				if (dist[nR][nC] > newDist)
				{
					pq.push({ newDist,nR,nC });
					dist[nR][nC] = newDist;
				}
			}
		}
	}
}

void solve()
{
	dijkstra();

	vector<pair<int, int>> result;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (dist[i][j] <= Tg)
				continue;

			result.push_back({ i,j });
		}
	}

	for (int i{ 0 }; i < result.size(); ++i)
	{
		cout << result[i].first + 1 << ' ' << result[i].second + 1 << endl;
	}

	if (result.size() == 0)
		cout << -1;
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