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
using vertex = tuple<ll, int, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 201

int N, M, K, Q;
vector<vector<pair<int, int>>>edges(MAX, vector<pair<int, int>>());
vector<vector<ll>> dist(MAX, vector<ll>(2, INF));
vector<pair<int, int>> query;

void input()
{
	cin >> N >> M >> K >> Q;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
	}

	for (int i{ 0 }; i < Q; ++i)
	{
		int src, dst;

		cin >> src >> dst;

		query.push_back({ src,dst });
	}
}

ll dijkstra(int start, int end)
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	if (start <= K)
	{
		dist[start][1] = 0;
		pq.push({ 0,start,1 });
	}
	else
	{
		dist[start][0] = 0;
		pq.push({ 0,start,0 });
	}

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto state{ get<2>(cur) };

		if (dist[src][state] < curDist)
			continue;

		if (src == end && state == 1)
		{
			return curDist;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };
			auto newState{ state };

			if (dst <= K)
				newState = 1;

			if (dist[dst][newState] > newDist)
			{
				dist[dst][newState] = newDist;
				pq.push({ newDist,dst,newState });
			}
		}
	}

	return INF;
}

void solve()
{
	int cnt{ 0 };
	ll total{ 0 };

	for (int i{ 0 }; i < query.size(); ++i)
	{
		dist = vector<vector<ll>>(MAX, vector<ll>(2, INF));

		int src{ query[i].first };
		int dst{ query[i].second };

		auto result{ dijkstra(src,dst) };

		if (result == INF)
			continue;
		else
		{
			total += result;
			++cnt;
		}
	}

	cout << cnt << endl;
	cout << total;
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