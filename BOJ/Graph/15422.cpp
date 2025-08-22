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
*	1. Ư�� ���� �ϳ��� ����� �������� �� ���� �ּ� ����� ���ؾ� �Ѵ�.
*	2. Ư�� �������� ������ �������� ���� ���� �������� �ʾ��� ���� ����� ������ 2���� dist �迭�� �����Ѵ�.
*	3. ���ͽ�Ʈ�� �˰����� �����ϸ鼭, ���� ������ ���� ���� ���ο� ���� ���� �� ����� ���� ��쿡�� �湮�Ѵ�.
*/

using namespace std;
using ll = long long;
using vertex = tuple<ll, int, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 50'001

int N, M, F, S, T;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<ll>> dist(MAX, vector<ll>(2, INF));

unordered_multimap<int, int> flight;

void input()
{
	cin >> N >> M >> F >> S >> T;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	for (int i{ 0 }; i < F; ++i)
	{
		int src, dst;
		cin >> src >> dst;

		flight.insert({ src,dst });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,S,0 });
	dist[S][0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto flightUsage{ get<2>(cur) };

		if (dist[src][flightUsage] < curDist)
			continue;

		if (src == T)
		{
			cout << curDist;
			return;
		}

		auto range = flight.equal_range(src);

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst][flightUsage] > newDist)
			{
				dist[dst][flightUsage] = newDist;
				pq.push({ newDist,dst,flightUsage });
			}
		}

		if (flightUsage == false)
		{
			for (auto it{ range.first }; it != range.second; ++it)
			{
				auto newDist_canFlight{ curDist };

				auto dst{ it->second };

				if (dist[dst][true] > newDist_canFlight)
				{
					dist[dst][true] = newDist_canFlight;
					pq.push({ newDist_canFlight,dst,true });
				}
			}
		}
	}
}

void solve()
{
	dijkstra();
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