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

#define MAX 100'001
#define endl '\n'
#define INF numeric_limits<ll>::max()

int N, M, K, S, p, q;
vector<vector<int>> edges(MAX, vector<int>());
set<int> infected;
vector<ll> dist_Infected(MAX, INF);
vector<ll> dist(MAX, INF);

void input()
{
	cin >> N >> M >> K >> S >> p >> q;

	for (int i{ 0 }; i < K; ++i)
	{
		int v;
		cin >> v;

		infected.insert(v);
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst;
		cin >> src >> dst;

		edges[src].push_back(dst);
		edges[dst].push_back(src);
	}
}

void dijkstra_Infected()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	for (auto& v : infected)
	{
		pq.push({ 0,v });
		dist_Infected[v] = 0;
	}

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		ll src{ get<1>(cur) };
		ll curDist{ get<0>(cur) };

		if (dist_Infected[src] < curDist)
			continue;

		for (auto& dst : edges[src])
		{
			ll newDist{ curDist + 1 };

			if (dist_Infected[dst] > newDist)
			{
				dist_Infected[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}

	dist_Infected[1] = INF;
	dist_Infected[N] = INF;
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

		ll src{ get<1>(cur) };
		ll curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		for (auto& dst : edges[src])
		{
			if (infected.find(dst) != infected.end())
				continue;

			ll w{ 0 };

			if (dist_Infected[dst] > S)
				w = p;
			else
				w = q;

			if (dst == N)
				w = 0;

			ll newDist{ curDist + w };

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	dijkstra_Infected();
	dijkstra();

	cout << dist[N];
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