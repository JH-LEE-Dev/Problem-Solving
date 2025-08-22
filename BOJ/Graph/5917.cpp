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
*	문제 이해
*	1. M개의 간선 중에서 하나의 간선의 가중치를 두 배로 했을 경우, 최소 비용이 가장 크게 상승하는 값을 제출.
*	2. 연결 그래프이고, 양방향 간선이다.
*	3. N == 100, M == 10'000
*
*	문제 해결 전략
*	1. 최단 거리를 구성하는 간선들 중에서 하나씩 가중치를 2배로 설정하며 다익스트라를 실행.
*	   최소 비용이 가장 크게 증가하는 값을 추려내서 제출.
*/

using namespace std;
using vertex = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N, M;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<pair<int, int>> shortestPath;
vector<int> dist(MAX, INF);
vector<int> parent(MAX, -1);

int shortestValue{ INF };
int result{ -1 };

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,1 });
	dist[1] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
				parent[dst] = src;
			}
		}
	}

	auto cursor{ N };

	while (cursor != -1)
	{
		if (parent[cursor] != -1)
		{
			shortestPath.push_back({ parent[cursor],cursor });
		}

		cursor = parent[cursor];
	}
}

void dijkstra_doubled(int idx)
{
	pair<int, int> doubledEdge{ shortestPath[idx] };

	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,1 });
	dist[1] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (src == doubledEdge.first && dst == doubledEdge.second
				|| src == doubledEdge.second && dst == doubledEdge.first)
			{
				newDist += w;
			}

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
				parent[dst] = src;
			}
		}
	}
}

void solve()
{
	dijkstra();

	shortestValue = dist[N];

	for (int i{ 0 }; i < shortestPath.size(); ++i)
	{
		dist = vector<int>(MAX, INF);

		dijkstra_doubled(i);

		result = max(result, abs(dist[N] - shortestValue));
	}

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