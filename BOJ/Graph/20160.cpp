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

using ll = long long;
using namespace std;
using vertex = tuple<ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 10'001

int N, M;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> stopBy;
int s;
ll result{ INF };

vector<ll> dist_stopBy(MAX, INF);
vector<ll> dist(MAX, INF);
vector<ll> startDist(10, 0);


void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	for (int i{ 0 }; i < 10; ++i)
	{
		int temp;
		cin >> temp;

		stopBy.push_back(temp);
	}

	cin >> s;
}

void dijkstra_stopBy(int v, ll start)
{
	dist_stopBy = vector<ll>(MAX, INF);

	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ start,v });
	dist_stopBy[v] = start;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist_stopBy[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist_stopBy[dst] > newDist)
			{
				dist_stopBy[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,s });
	dist[s] = 0;

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
	if (s == stopBy[0])
		result = min(result, (ll)stopBy[0]);

	dijkstra();

	int idx{ 0 };

	while (true)
	{
		dijkstra_stopBy(stopBy[idx], startDist[idx]);

		++idx;

		while (true)
		{
			if (idx == 10)
				break;

			if (dist_stopBy[stopBy[idx]] == INF)
				++idx;
			else
				break;
		}

		if (idx == 10)
			break;

		startDist[idx] = dist_stopBy[stopBy[idx]];

		if (dist[stopBy[idx]] == INF)
			continue;

		if (dist[stopBy[idx]] <= dist_stopBy[stopBy[idx]])
			result = min(result, (ll)stopBy[idx]);
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