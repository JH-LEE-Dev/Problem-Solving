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
#define MAX 501

int N;
vector<vector<int>> edges(MAX, vector<int>());
vector<int> times(MAX, 0);
vector<int> InitTimes(MAX, 0);
vector<int> indegree(MAX, 0);

void input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		cin >> times[i];

		InitTimes[i] = times[i];

		while (true)
		{
			int temp;
			cin >> temp;

			if (temp == -1)
				break;

			edges[temp].push_back(i);
			++indegree[i];
		}
	}
}

void toposort()
{
	queue<int> q;

	for (int i{ 1 }; i <= N; ++i)
	{
		if (indegree[i] == 0)
			q.push(i);
	}

	while (q.empty() == false)
	{
		auto src{ q.front() };
		q.pop();

		for (auto dst : edges[src])
		{
			times[dst] = max(times[dst], times[src] + InitTimes[dst]);
			--indegree[dst];

			if (indegree[dst] == 0)
				q.push(dst);
		}
	}
}

void solve()
{
	toposort();

	for (int i{ 1 }; i <= N; ++i)
	{
		cout << times[i] << endl;
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