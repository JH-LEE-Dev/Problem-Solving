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
#define MAX 501

int N, M, K;
vector<vector<tuple<int, int, int>>> edges(MAX, vector<tuple<int, int, int>>());
vector<vector<ll>> dist(MAX, vector<ll>(MAX, INF));

ll result{ INF };

void input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w, k;

		cin >> src >> dst >> w >> k;

		edges[src].push_back({ dst,w,k });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,1,0 });
	dist[1][0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curK{ get<2>(cur) };

		if (dist[src][curK] < curDist)
			continue;

		if (src == N)
		{
			result = curDist;
			return;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ get<0>(edge) };
			auto w{ get<1>(edge) };
			auto k{ get<2>(edge) };
			auto newDist{ curDist + w };
			auto remain{ k - (curDist % k) };

			if (curDist % k != 0)
			{
				if (curK < K)
				{
					if (dist[dst][curK + 1] > newDist)
					{
						dist[dst][curK + 1] = newDist;
						pq.push({ newDist,dst,curK + 1 });
					}
				}
			}

			if (curDist % k != 0)
				newDist += remain;

			if (dist[dst][curK] > newDist)
			{
				dist[dst][curK] = newDist;
				pq.push({ newDist,dst,curK });
			}
		}
	}
}

void solve()
{
	dijkstra();

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