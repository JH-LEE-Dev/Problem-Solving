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
#define MAX 101

int N{ 0 };
vector<vector<int>> edges(MAX, vector<int>());
vector<int> visited(MAX, false);
bool result{ false };

void input()
{
	cin >> N;

	for (int i{ 1 }; i < N; ++i)
	{
		int cnt{ 0 };
		cin >> cnt;

		for (int j{ 0 }; j < cnt; ++j)
		{
			int dst{ 0 };
			cin >> dst;

			edges[i].push_back({ dst });
		}
	}
}

void dfs(int src)
{
	if (result == true)
		return;

	visited[src] = true;

	for (auto& dst : edges[src])
	{
		if (visited[dst] == false)
		{
			dfs(dst);
		}
		else
		{
			result = true;
			return;
		}
	}

	visited[src] = false;
}

void solve()
{
	dfs(1);

	if (result)
		cout << "CYCLE";
	else
		cout << "NO CYCLE";
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