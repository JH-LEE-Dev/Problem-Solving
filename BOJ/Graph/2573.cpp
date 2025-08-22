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

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 301

int N, M;

vector<vector<int>> table(MAX, vector<int>(MAX, 0));
vector<vector<bool>> visited(MAX, vector<bool>(MAX, false));

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

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

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0)
		return false;
	else
		return true;
}

void bfs(int sR, int sC)
{
	auto _table = table;

	queue<tuple<int, int>> q;
	q.push({ sR,sC });
	vector<vector<bool>> visited(MAX, vector<bool>(MAX, false));
	visited[sR][sC] = true;

	while (q.empty() == false)
	{
		auto cur{ q.front() };
		q.pop();

		auto r{ get<0>(cur) };
		auto c{ get<1>(cur) };

		int cnt{ 0 };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			if (table[nR][nC] == 0)
			{
				++cnt;
				continue;
			}

			if (visited[nR][nC] == false)
			{
				visited[nR][nC] = true;
				q.push({ nR,nC });
			}
		}

		_table[r][c] -= cnt;

		if (_table[r][c] < 0)
			_table[r][c] = 0;
	}

	table = _table;
}

void dfs(int r, int c)
{
	visited[r][c] = true;

	for (int i{ 0 }; i < 4; ++i)
	{
		auto nR{ r + dir_row[i] };
		auto nC{ c + dir_col[i] };

		if (isValid(nR, nC) == false)
			continue;

		if (table[nR][nC] == 0)
			continue;

		if (visited[nR][nC] == false)
		{
			dfs(nR, nC);
		}
	}
}

void solve()
{
	int t{ 1 };

	while (true)
	{
		visited = vector<vector<bool>>(MAX, vector<bool>(MAX, false));

		bool bfsSucceed{ false };

		for (int i{ 0 }; i < N; ++i)
		{
			for (int j{ 0 }; j < M; ++j)
			{
				if (table[i][j] != 0)
				{
					bfs(i, j);
					bfsSucceed = true;
					break;
				}
			}

			if (bfsSucceed == true)
				break;
		}

		if (bfsSucceed == false)
		{
			cout << 0;
			return;
		}

		bool dfsSucceed{ false };

		for (int i{ 0 }; i < N; ++i)
		{
			for (int j{ 0 }; j < M; ++j)
			{
				if (dfsSucceed && visited[i][j] == false && table[i][j] != 0)
				{
					cout << t;
					return;
				}

				if (visited[i][j] == false && table[i][j] != 0)
				{
					dfsSucceed = true;
					dfs(i, j);
				}
			}
		}

		++t;
	}
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