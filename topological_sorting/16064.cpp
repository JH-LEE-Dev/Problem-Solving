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
*	1. DAG에서의 Shortest Path는 위상 정렬을 사용할 수 있다.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int N, M;

vector<vector<int>> edges(MAX, vector<int>(MAX, 0));
vector<int> indegree(MAX, 0);
vector<int> dist(MAX, 0);
queue<int> q;

int result{ 0 };

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		if (edges[src][dst] != 0)
		{
			edges[src][dst] = max(edges[src][dst], w);
		}
		else
		{
			++indegree[dst];
			edges[src][dst] = w;
		}
	}
}

void toposort()
{
	while (q.empty() == false)
	{
		auto src{ q.front() };
		q.pop();

		result = max(result, dist[src]);

		for (int i{ 1 }; i <= N; ++i)
		{
			if (edges[src][i] == 0)
				continue;

			--indegree[i];

			dist[i] = max(dist[src] + edges[src][i], dist[i]);

			if (indegree[i] == 0)
				q.push(i);
		}
	}
}

void solve()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		if (indegree[i] == 0)
			q.push(i);
	}

	toposort();

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