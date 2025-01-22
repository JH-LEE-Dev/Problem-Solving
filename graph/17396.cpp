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

int N{ 0 }, M{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);
vector<bool> wards(MAX, false);


void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;

		wards[i] = (bool)input;
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,0 });
	dist[0] = 0;

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
				if (dst == N - 1)
				{
					pq.push({ newDist,dst });
					dist[dst] = newDist;
				}
				else
				{
					if (wards[dst] == false)
					{
						pq.push({ newDist,dst });
						dist[dst] = newDist;
					}
				}
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (dist[N - 1] == INF)
		cout << -1;
	else
		cout << dist[N - 1];
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}