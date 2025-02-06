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
#define MAX 100'001

ll N{ 0 }, M{ 0 }, D{ 0 }, E{ 0 };
vector<vector<pair<ll, ll>>> edges(MAX, vector<pair<ll, ll>>());
vector<ll> heights;
vector<ll> dist_fromHome(MAX, INF);
vector<ll> dist_fromSchool(MAX, INF);

void input()
{
	cin >> N >> M >> D >> E;

	for (int i{ 0 }; i < N; ++i)
	{
		ll h{ 0 };
		cin >> h;

		heights.push_back(h);
	}

	for (int i{ 0 }; i < M; ++i)
	{
		ll src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra_fromHome()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,1 });
	dist_fromHome[1] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto h_src{ heights[src - 1] };

		if (dist_fromHome[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second * D };
			auto h_dst{ heights[dst - 1] };
			auto newDist{ curDist + w };

			if (h_src >= h_dst || dst == N)
				continue;

			if (dist_fromHome[dst] > newDist)
			{
				pq.push({ newDist,dst });
				dist_fromHome[dst] = newDist;
			}
		}
	}
}

void dijkstra_fromSchool()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,N });
	dist_fromSchool[N] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto h_src{ heights[src - 1] };

		if (dist_fromSchool[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second * D };
			auto h_dst{ heights[dst - 1] };
			auto newDist{ curDist + w };

			if (h_src >= h_dst || dst == 1)
				continue;

			if (dist_fromSchool[dst] > newDist)
			{
				pq.push({ newDist,dst });
				dist_fromSchool[dst] = newDist;
			}
		}
	}
}

void solve()
{
	dijkstra_fromHome();
	dijkstra_fromSchool();

	ll result{ -INF };

	for (int i{ 1 }; i <= N; ++i)
	{
		if (dist_fromHome[i] == INF || dist_fromSchool[i] == INF)
			continue;

		auto h{ heights[i - 1] };
		auto HE{ h * E };
		auto total{ HE - (dist_fromHome[i] + dist_fromSchool[i]) };

		if (total > result)
		{
			result = total;
		}
	}

	if (result == -INF)
		cout << "Impossible";
	else
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