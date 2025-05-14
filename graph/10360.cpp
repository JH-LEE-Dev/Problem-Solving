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
#define MAX 2'001

int T;
int N, M;
vector<tuple<int, int, int>> edges;
vector<vector<int>> graph(MAX, vector<int>());
vector<int> dist(MAX, INF);
vector<bool> visited(MAX, false);

vector<int> cycle;

void input()
{
	dist = vector<int>(MAX, INF);
	edges.clear();
	cycle.clear();
	graph = vector<vector<int>>(MAX, vector<int>());
	visited = vector<bool>(MAX, false);

	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges.push_back({ src,dst,w });
		graph[src].push_back(dst);
	}
}

void bellmanFord()
{
	dist[0] = 0;

	for (int i{ 0 }; i < N - 1; ++i)
	{
		for (auto& edge : edges)
		{
			auto src{ get<0>(edge) };
			auto dst{ get<1>(edge) };
			auto w{ get<2>(edge) };

			if (dist[src] == INF)
				continue;

			dist[dst] = min(dist[dst], dist[src] + w);
		}
	}

	for (auto& edge : edges)
	{
		auto src{ get<0>(edge) };
		auto dst{ get<1>(edge) };
		auto w{ get<2>(edge) };

		if (dist[src] == INF)
			continue;

		if (dist[dst] > dist[src] + w)
		{
			dist[dst] = dist[src] + w;
			cycle.push_back(src);
		}
	}
}

bool bfs(int start)
{
	visited[start] = true;
	queue<int> q;
	q.push(start);

	while (q.empty() == false)
	{
		auto src{ q.front() };
		q.pop();

		for (auto& dst : graph[src])
		{
			if (visited[dst] == false)
			{
				visited[dst] = true;
				q.push(dst);
			}
		}
	}

	return visited[0];
}

void solve()
{
	cin >> T;

	int cnt{ 1 };

	while (T != 0)
	{
		input();
		bellmanFord();

		bool result{ false };

		//cycle이 여러 개 있을 수 있으므로, bfs(cycle[0])으로만 해서는 안되고 모든 사이클에 대해서 bfs를 실행해봐야 한다.
		for (auto& v : cycle)
		{
			if (visited[v] == false)
				result = bfs(v);

			if (result)
				break;
		}

		if (result)
			cout << "Case #" << cnt << ": possible" << endl;
		else
			cout << "Case #" << cnt << ": not possible" << endl;

		++cnt;
		--T;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}