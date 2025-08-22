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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 3'001

int N{ 0 }, M{ 0 }, K{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> parent(MAX, -1);
vector<ll> dist(MAX, INF);
vector<int> shop;
ll result{ -1 };

void dijkstra()
{
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> myPQ;

	for (int i{ 0 }; i < K; ++i)
	{
		myPQ.push({ 0,shop[i] });
		dist[shop[i]] = 0;
	}

	while (myPQ.empty() == false)
	{
		auto cur{ myPQ.top() };
		myPQ.pop();

		auto src{ cur.second };
		auto curDist{ cur.first };

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
				parent[dst] = src;
				myPQ.push({ newDist,dst });
			}
		}
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		for (auto& edge : edges[i])
		{
			auto dst{ edge.first };
			auto w{ edge.second };

			if (dist[dst] != INF && parent[i] != dst)
			{
				ll delta{ (ll)ceil(abs(((double)dist[i] - (double)((w + dist[dst]))) / 2)) };
				delta += dist[i];
				result = max(delta, result);
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M >> K;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int input{ 0 };
		cin >> input;

		shop.push_back(input);
	}

	dijkstra();

	cout << result;

	return 0;
}