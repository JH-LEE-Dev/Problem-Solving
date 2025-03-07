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

#define DIV 1'000'000'009
#define endl '\n'
#define INF numeric_limits<ll>::max()

#define MAX 100'001

int N, M, S, E;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);
vector<ll> cache(MAX, -1);

ll result{ 0 };

void input()
{
	cin >> N >> M >> S >> E;

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
	pq.push({ 0,S });
	dist[S] = 0;

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
			auto newDist{ curDist + (ll)w };

			if (dist[dst] > newDist)
			{
				pq.push({ newDist,dst });
				dist[dst] = newDist;
			}
		}
	}
}

int dfs(int v)
{
	if (v == S)
		return 1;

	ll ret{ cache[v] };

	if (ret != -1)
		return cache[v];

	ret = 0;

	for (auto& edge : edges[v])
	{
		auto dst{ edge.first };
		auto w{ edge.second };

		if (dist[v] == dist[dst] + w)
		{
			ret = (ret + dfs(dst)) % DIV;
		}
	}

	cache[v] = ret;

	return ret;
}

void solve()
{
	dijkstra();
	cout << dfs(E);
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