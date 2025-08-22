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
*		문제 해결 전략
*		1. 다익스트라 알고리즘을 사용한다.
*		2. 각 층에서, 각 방을 이동할 때 엘리베이터를 만나면 K층으로 이동하는 비용을 저장한다.
*		3. N번 방에서 역방향 다익스트라를 실행해서, 각 방에서 K층으로 이동하는 비용 + N번 방에서 각 방으로 이동하는 비용 중에서
*		최소값을 제출한다.
*/

using namespace std;
using ll = long long;
using vertex = tuple<ll, ll>;

#define endl '\n'
#define INF (ll)1e18
#define MAX 100'001

ll N, M, K;
vector<vector<pair<ll, ll>>> edges(MAX, vector<pair<ll, ll>>());
vector<ll> dist(MAX, INF);
vector<ll> dist_Reverse(MAX, INF);

void input()
{
	cin >> N >> M >> K;

	for (ll i{ 0 }; i < M; ++i)
	{
		ll src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
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
			}
		}
	}
}

void dijkstra_reverse()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,N });
	dist_Reverse[N] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist_Reverse[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist_Reverse[dst] > newDist)
			{
				dist_Reverse[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	dijkstra();
	dijkstra_reverse();

	ll result{ INF };

	for (ll i{ 1 }; i <= N; ++i)
	{
		ll elevator;

		cin >> elevator;

		if (elevator == -1)
			continue;

		result = min(dist[i] + elevator * (K - 1) + dist_Reverse[i], result);
	}

	if (result == INF)
		cout << -1;
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