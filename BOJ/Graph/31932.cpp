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

int N, M;
vector<vector<tuple<int, int, int>>> edges(MAX, vector<tuple<int, int, int>>());
vector<ll> dist(MAX, INF);

int result{ -1 };

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w, t;

		cin >> src >> dst >> w >> t;

		edges[src].push_back({ dst,w,t });
		edges[dst].push_back({ src,w,t });
	}
}

bool dijkstra(ll start)
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	dist[1] = start;
	pq.push({ start,1 });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		if (src == N)
		{
			return true;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ get<0>(edge) };
			auto w{ get<1>(edge) };
			auto t{ get<2>(edge) };
			auto newDist{ curDist + w };

			if (t < newDist)
				continue;

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}

	return false;
}

void bSearch()
{
	int left{ 0 };
	int right{ 1'000'000'001 };

	while (left <= right)
	{
		dist = vector<ll>(MAX, INF);
		int middle{ (left + right) / 2 };

		if (dijkstra(middle))
		{
			left = middle + 1;

			result = max(result, middle);
		}
		else
			right = middle - 1;
	}
}

void solve()
{
	bSearch();

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