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
using vertex = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()/2
#define MAX 10'001

int N, M, K;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> shop(6, 0);
vector<vector<int>> dist(MAX, vector<int>(6, INF));
vector<int> idx(MAX, -1);

void input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < K; ++i)
	{
		cin >> shop[i];

		idx[shop[i]] = i;
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra(int start)
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	pq.push({ 0,shop[start] });
	dist[shop[start]][start] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src][start] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst][start] > newDist)
			{
				dist[dst][start] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

int usePermutation(int start)
{
	int result = INF;
	vector<int> permutation;

	for (int i = 0; i < K; i++)
	{
		permutation.push_back(shop[i]);
	}

	do {
		int total = 0;

		total += dist[start][idx[permutation[0]]];

		for (int i = 0; i < K - 1; i++) {
			total += dist[permutation[i + 1]][idx[permutation[i]]];
		}

		total += dist[start][idx[permutation[K - 1]]];

		result = min(result, total);

	} while (next_permutation(permutation.begin(), permutation.end()));

	return result;
}

void solve()
{
	for (int i{ 0 }; i < K; ++i)
	{
		dijkstra(i);
	}

	int result{ INF };

	for (int i{ 1 }; i <= N; ++i)
	{
		if (idx[i] != -1)
			continue;

		result = min(result, usePermutation(i));
	}

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