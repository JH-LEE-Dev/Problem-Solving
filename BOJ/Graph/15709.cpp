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
#define MAX 20'301

int N, M, B, K, Q;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<pair<int, int>> query;
vector<vector<ll>> dist(MAX, vector<ll>(101, INF));

void input()
{
	cin >> N >> M >> B >> K >> Q;

	for (int i{ 0 }; i < K; ++i)
	{
		int src, dst, w;
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	for (int i{ 0 }; i < Q; ++i)
	{
		int src, dst;
		cin >> src >> dst;

		query.push_back({ src,dst });
	}
}

void dijkstra(int start)
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	dist[N + M + start][start] = 0;
	pq.push({ 0,N + M + start });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src][start] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst][start] > newDist)
			{
				dist[dst][start] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	for (int i{ 1 }; i <= B; ++i)
	{
		dijkstra(i);
	}

	for (int i{ 0 }; i < Q; ++i)
	{
		int src{ query[i].first };
		int dst{ query[i].second };

		ll result{ INF };

		for (int j{ 1 }; j <= B; ++j)
		{
			if (dist[src][j] == INF || dist[dst][j] == INF)
				continue;

			result = min(dist[src][j] + dist[dst][j], result);
		}

		if (result == INF)
			cout << -1 << endl;
		else
			cout << result << endl;
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