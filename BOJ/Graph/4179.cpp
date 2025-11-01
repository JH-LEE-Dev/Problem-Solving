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
using state = tuple<int, int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int n, m;
vector<vector<char>> table(MAX, vector<char>(MAX, '.'));
pair<int, int> start;
vector<pair<int, int>> fires;
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

bool IsValid(int r, int c)
{
	if (r >= n || r < 0 || c >= m || c < 0 || table[r][c] == '#')
		return false;
	else
		return true;
}

bool IsOut(int r, int c)
{
	if (r == n - 1 || r == 0 || c == m - 1 || c == 0)
		return true;
	else
		return false;
}

void Input()
{
	cin >> n >> m;

	for (int i{ 0 }; i < n; ++i)
	{
		for (int j{ 0 }; j < m; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == 'J')
				start = { i,j };

			if (table[i][j] == 'F')
				fires.push_back({ i,j });
		}
	}
}

void Bfs()
{
	queue<state> q;

	for (int i{ 0 }; i < fires.size(); ++i)
	{
		q.push({ fires[i].first,fires[i].second,1,0 });
		dist[fires[i].first][fires[i].second] = 0;
	}

	q.push({ start.first,start.second,0,0 });
	dist[start.first][start.second] = 0;

	while (q.empty() == false)
	{
		auto cur{ q.front() };
		q.pop();

		auto [r, c, type, t] {cur};

		if (type == 0)
		{
			if (IsOut(r, c))
			{
				cout << t + 1;
				return;
			}
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto newR{ r + dir_row[i] };
			auto newC{ c + dir_col[i] };
			auto newDist{ t + 1 };

			if (IsValid(newR, newC) == false || table[newR][newC] == 'F')
				continue;

			if (dist[newR][newC] > newDist)
			{
				dist[newR][newC] = newDist;
				q.push({ newR,newC,type,newDist });
			}
		}
	}

	cout << "IMPOSSIBLE";
}

void Solve()
{
	Bfs();
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();

	return 0;
}