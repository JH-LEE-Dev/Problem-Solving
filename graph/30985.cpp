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
*		���� �ذ� ����
*		1. ���ͽ�Ʈ�� �˰����� ����Ѵ�.
*		2. �� ������, �� ���� �̵��� �� ���������͸� ������ K������ �̵��ϴ� ����� �����Ѵ�.
*		3. N�� �濡�� ������ ���ͽ�Ʈ�� �����ؼ�, �� �濡�� K������ �̵��ϴ� ��� + N�� �濡�� �� ������ �̵��ϴ� ��� �߿���
*		�ּҰ��� �����Ѵ�.
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