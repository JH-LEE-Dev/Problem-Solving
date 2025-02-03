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
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 501

int N{ 0 }, M{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
vector<int> dir_row{ 0,0,-1,1 };
vector<int> dir_col{ -1,1,0,0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

bool isValid(int r, int c)
{
	if (r >= MAX || r < 0 || c >= MAX || c < 0)
		return false;
	else
		return true;
}

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int x1{ 0 }, y1{ 0 }, x2{ 0 }, y2{ 0 };

		cin >> x1 >> y1 >> x2 >> y2;

		if (x1 > x2)
			swap(x1, x2);

		if (y1 > y2)
			swap(y1, y2);

		for (int i{ x1 }; i <= x2; ++i)
		{
			for (int j{ y1 }; j <= y2; ++j)
			{
				table[i][j] = 1;
			}
		}
	}

	cin >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int x1{ 0 }, y1{ 0 }, x2{ 0 }, y2{ 0 };

		cin >> x1 >> y1 >> x2 >> y2;

		if (x1 > x2)
			swap(x1, x2);

		if (y1 > y2)
			swap(y1, y2);

		for (int i{ x1 }; i <= x2; ++i)
		{
			for (int j{ y1 }; j <= y2; ++j)
			{
				table[i][j] = INF;
			}
		}
	}
}

void bfs()
{
	deque<vertex> dq;
	dq.push_front({ 0,0,0 });
	dist[0][0] = 0;

	while (dq.empty() == false)
	{
		auto cur{ dq.front() };
		dq.pop_front();

		auto row{ get<0>(cur) };
		auto col{ get<1>(cur) };
		auto curDist{ get<2>(cur) };

		if (dist[row][col] < curDist)
			continue;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ row + dir_row[i] };
			auto nC{ col + dir_col[i] };
			auto newDist{ curDist };

			if (isValid(nR, nC) == false || table[nR][nC] == INF)
				continue;

			if (table[nR][nC] == 1)
			{
				newDist += 1;

				if (dist[nR][nC] > newDist)
				{
					dist[nR][nC] = newDist;
					dq.push_back({ nR,nC,newDist });
				}
			}
			else
			{
				if (dist[nR][nC] > curDist)
				{
					dist[nR][nC] = curDist;
					dq.push_back({ nR,nC,curDist });
				}
			}
		}
	}
}

void solve()
{
	bfs();
	auto result{ dist[MAX - 1][MAX - 1] };

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