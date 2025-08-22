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
using vertex = tuple<ll, ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 100'001

int N, M;
int start, goal;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> water(MAX, 0);

vector<pair<ll, ll>> dist(MAX, { INF,INF });

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> water[i + 1];
	}

	cin >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	cin >> start >> goal;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,-water[start],start });
	dist[start] = make_pair(0, -water[start]);

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<2>(cur) };
		auto curDist{ get<0>(cur) };
		auto curWater{ get<1>(cur) };

		if (dist[src] < make_pair(curDist, curWater))
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };
			auto newWater{ curWater - water[dst] };

			if (dist[dst] > make_pair(newDist, newWater))
			{
				dist[dst] = make_pair(newDist, newWater);
				pq.push({ newDist,newWater,dst });
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (dist[goal].first == INF)
		cout << -1;
	else
		cout << dist[goal].first << ' ' << -dist[goal].second;
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