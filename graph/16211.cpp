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
#define MAX 200'001

int N, M, K;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);
vector<ll> dist_people(MAX, INF);
vector<int> people;

void input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int temp;
		cin >> temp;

		people.push_back(temp);
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
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

			if (dist_people[dst] <= newDist)
				continue;

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void dijkstra_people()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	for (int i{ 0 }; i < K; ++i)
	{
		pq.push({ 0,people[i] });
		dist_people[people[i]] = 0;
	}

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist_people[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist_people[dst] > newDist)
			{
				dist_people[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	dijkstra_people();

	dijkstra();

	vector<int> result;

	for (int i{ 2 }; i <= N; ++i)
	{
		if (dist[i] == INF)
			continue;

		result.push_back(i);
	}

	if (result.empty() == false)
		for (auto& v : result)
			cout << v << ' ';
	else
		cout << 0;
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