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
#define MAX 10'001

ll N, M, T;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> cows(MAX, 0);
vector<ll> dist(MAX, INF);

void input()
{
	cin >> N >> M >> T;

	for (int i{ 0 }; i < N; ++i)
	{
		int temp;
		cin >> temp;

		cows[i + 1] = temp;
	}

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
	dist[1] = 0;
	pq.push({ 0,1 });

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

void solve()
{
	dijkstra();

	auto totalCnt = cows;

	priority_queue<vertex> pq;

	for (int i{ 1 }; i <= N; ++i)
	{
		pq.push({ dist[i],i });
	}

	//핵심 코드 : 출발 정점에서부터 거리가 먼 순서부터 사전순으로 부모 정점에 소의 수를 누적.
	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		int resultDst{ numeric_limits<int>::max() };

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst] + w == curDist)
			{
				resultDst = min(resultDst, dst);
			}
		}

		if (resultDst != numeric_limits<int>::max())
			totalCnt[resultDst] += totalCnt[src];
	}

	ll result{ 0 };

	for (int i{ 1 }; i <= N; ++i)
	{
		result = max(result, totalCnt[i] * dist[i] - totalCnt[i] * T);
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