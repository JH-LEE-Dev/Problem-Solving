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
using state = tuple<ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 100'001

int n, m;
int p, g;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist_p(MAX, INF);
vector<ll> dist_p_forbiddenG(MAX, INF);
vector<ll> dist_g(MAX, INF);

void Input()
{
	cin >> n >> m >> p >> g;

	for (int i{ 0 }; i < m; ++i)
	{
		int src, dst, w;
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra_p()
{
	priority_queue<state, vector<state>, greater<state>> pq;
	pq.push({ 0,p });
	dist_p[p] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto [curDist, src] {cur};

		if (dist_p[src] < curDist)
			continue;

		for (const auto& edge : edges[src])
		{
			auto [dst, w] {edge};
			auto newDist{ curDist + w };

			if (dist_p[dst] > newDist)
			{
				dist_p[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void dijkstra_p_forbiddenG()
{
	priority_queue<state, vector<state>, greater<state>> pq;
	pq.push({ 0,p });
	dist_p_forbiddenG[p] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto [curDist, src] {cur};

		if (dist_p_forbiddenG[src] < curDist)
			continue;

		for (const auto& edge : edges[src])
		{
			auto [dst, w] {edge};
			auto newDist{ curDist + w };

			if (dst == g)
				continue;

			if (dist_p_forbiddenG[dst] > newDist)
			{
				dist_p_forbiddenG[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void dijkstra_g()
{
	priority_queue<state, vector<state>, greater<state>> pq;
	pq.push({ 0,g });
	dist_g[g] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto [curDist, src] {cur};

		if (dist_p[src] < curDist)
			continue;

		for (const auto& edge : edges[src])
		{
			auto [dst, w] {edge};
			auto newDist{ curDist + w };

			if (dist_g[dst] > newDist)
			{
				dist_g[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void Solve()
{
	dijkstra_p();
	dijkstra_p_forbiddenG();
	dijkstra_g();

	ll ptog{ dist_p[g] };

	vector<int> result;

	for (int i{ 1 }; i <= n; ++i)
	{
		if (dist_p[i] != ptog * 2 || dist_p_forbiddenG[i] == ptog * 2)
			continue;

		if (dist_g[i] == ptog)
			result.push_back(i);
	}

	if (result.empty())
	{
		cout << '*';
		return;
	}

	for (const auto& v : result)
	{
		cout << v << ' ';
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();

	return 0;
}