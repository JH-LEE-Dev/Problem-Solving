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
#define MAX 30'001

vector<int> parent(MAX, -1);
vector<int> ran(MAX, -1);

int n, m, k;
vector<int> cnt(MAX, 1);
vector<int> candyCnt(MAX, 0);
vector<pair<int, int>> unions;
vector<vector<int>> DP(MAX, vector<int>(3'001, 0));

int Find(int u)
{
	if (parent[u] == u)
		return u;

	return parent[u] = Find(parent[u]);
}

void Merge(int u, int v)
{
	int par_u{ Find(u) };
	int par_v{ Find(v) };

	if (par_u == par_v)
		return;

	if (ran[par_u] > ran[par_v])
		swap(par_u, par_v);

	parent[par_u] = par_v;
	candyCnt[par_v] += candyCnt[par_u];
	cnt[par_v] += cnt[par_u];

	if (ran[par_u] == ran[par_v])
		++ran[par_v];
}

void Input()
{
	cin >> n >> m >> k;

	for (int i{ 1 }; i <= n; ++i)
	{
		parent[i] = i;
	}

	for (int i{ 0 }; i < n; ++i)
	{
		int temp;
		cin >> temp;

		candyCnt[i + 1] = temp;
	}

	for (int i{ 0 }; i < m; ++i)
	{
		int src, dst;
		cin >> src >> dst;

		Merge(src, dst);
	}
}

void Solve()
{
	vector<bool> visited(MAX, false);

	for (int i{ 1 }; i <= n; ++i)
	{
		int par{ Find(i) };
		if (visited[par] == true)
			continue;

		unions.push_back({ candyCnt[par],cnt[par] });
		visited[par] = true;
	}

	int num{ (int)unions.size() };

	for (int i{ 1 }; i <= num; ++i)
	{
		for (int j{ 1 }; j < k; ++j)
		{
			int curV{ unions[i - 1].first };
			int curW{ unions[i - 1].second };

			if (curW > j)
				DP[i][j] = DP[i - 1][j];
			else
				DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - curW] + curV);
		}
	}

	cout << DP[num][k - 1];
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