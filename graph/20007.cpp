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

#define MAX 1'001
#define endl '\n'
#define INF numeric_limits<ll>::max()

int N{ 0 }, M{ 0 }, X{ 0 }, Y{ 0 };
vector<vector<pair<int, ll>>> edges(MAX, vector<pair<int, ll>>());
vector<ll> dist(MAX, INF);

void input()
{
	cin >> N >> M >> X >> Y;

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
	pq.push({ 0,Y });
	dist[Y] = 0;

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

	ll time{ 0 };
	ll days{ 1 };

	sort(dist.begin(), dist.begin() + N);

	for (int i{ 0 }; i < N; ++i)
	{
		if (dist[i] == 0)
			continue;

		if (dist[i] * 2 > X)
		{
			cout << -1;
			return;
		}

		time += dist[i] * 2;

		if (time > X)
		{
			++days;
			time = dist[i] * 2;
		}
	}

	cout << days;
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