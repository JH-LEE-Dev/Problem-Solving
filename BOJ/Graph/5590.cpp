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
#define MAX 101

int N, K;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);

void input()
{
	cin >> N >> K;
}

ll dijkstra(int start, int end)
{
	dist = vector<ll>(MAX, INF);

	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,start });
	dist[start] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		if (src == end)
		{
			return curDist;
		}

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

	return INF;
}

void solve()
{
	for (int i{ 0 }; i < K; ++i)
	{
		int type, src, dst, w;

		cin >> type;

		if (type == 0)
		{
			cin >> src >> dst;

			auto result{ dijkstra(src,dst) };

			if (result == INF)
				cout << -1 << endl;
			else
				cout << result << endl;
		}
		else
		{
			cin >> src >> dst >> w;

			edges[src].push_back({ dst,w });
			edges[dst].push_back({ src,w });
		}
	}
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