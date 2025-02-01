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
using vertex = tuple<ll, int, bool>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 10'001

int N{ 0 }, M{ 0 };
int star_dist{ 0 }, mac_dist{ 0 };
int star_count{ 0 }, mac_count{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> mac;
vector<int> star;
vector<vector<ll>> dist(MAX, vector<ll>(2, INF));
vector<int> distLimit;

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	cin >> mac_count >> mac_dist;

	for (int i{ 0 }; i < mac_count; ++i)
	{
		int input{ 0 };
		cin >> input;

		mac.push_back(input);
	}

	cin >> star_count >> star_dist;

	for (int i{ 0 }; i < star_count; ++i)
	{
		int input{ 0 };
		cin >> input;

		star.push_back(input);
	}

	distLimit.push_back(mac_dist);
	distLimit.push_back(star_dist);
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;

	for (int i{ 0 }; i < mac_count; ++i)
	{
		dist[mac[i]][false] = 0;
		pq.push({ 0,mac[i],false });
	}

	for (int i{ 0 }; i < star_count; ++i)
	{
		dist[star[i]][true] = 0;
		pq.push({ 0,star[i],true });
	}

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curType{ get<2>(cur) };

		if (dist[src][curType] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (newDist > distLimit[curType])
				continue;

			if (dist[dst][curType] > newDist)
			{
				dist[dst][curType] = newDist;
				pq.push({ newDist,dst,curType });
			}
		}
	}
}

void solve()
{
	dijkstra();

	ll result{ INF };

	for (int i{ 1 }; i <= N; ++i)
	{
		if (dist[i][false] == 0 || dist[i][false] == INF)
			continue;

		if (dist[i][true] == 0 || dist[i][true] == INF)
			continue;

		result = min(result, dist[i][false] + dist[i][true]);
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