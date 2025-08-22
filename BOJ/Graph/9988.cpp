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
using ll = long long;
using vertex = tuple<ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 251

int N, M;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);
vector<pair<int, int>> path;
vector<int> parent(MAX, -1);

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

void dijkstra(int forbidden_src, int forbidden_dst)
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

			if ((forbidden_src == src && forbidden_dst == dst) ||
				(forbidden_src == dst && forbidden_dst == src))
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
	dijkstra(-1, -1);

	auto cursor{ N };
	while (cursor != -1)
	{
		if (parent[cursor] != -1)
			path.push_back({ cursor,parent[cursor] });

		cursor = parent[cursor];
	}

	ll initialDist{ dist[N] };
	ll result{ -1 };

	for (int i{ 0 }; i < path.size(); ++i)
	{
		dist = vector<ll>(MAX, INF);

		dijkstra(path[i].first, path[i].second);

		result = max(result, dist[N] - initialDist);
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