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
#define MAX 32'001

int N{ 0 }, M{ 0 };
vector<vector<int>> edges(MAX, vector<int>());
vector<int> indegree(MAX, 0);
vector<int> result;

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 };
		cin >> src >> dst;

		edges[src].push_back({ dst });
		++indegree[dst];
	}
}

void topoSort()
{
	priority_queue<int, vector<int>, greater<int>>pq;

	for (int i{ 1 }; i <= N; ++i)
	{
		if (indegree[i] == 0)
			pq.push(i);
	}

	while (pq.empty() == false)
	{
		auto src{ pq.top() };
		pq.pop();

		result.push_back(src);

		for (auto& dst : edges[src])
		{
			--indegree[dst];

			if (indegree[dst] == 0)
				pq.push(dst);
		}
	}
}

void solve()
{
	topoSort();

	for (auto& v : result)
	{
		cout << v << ' ';
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