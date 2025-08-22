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
#define INF numeric_limits<int>::max()
#define MAX 1'001

int N, M, X;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist(MAX, INF);

int result{ -1 };

void input()
{
	cin >> N >> M >> X;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,X });
	dist[X] = 0;

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
				pq.push({ newDist,dst });
				dist[dst] = newDist;
			}
		}
	}
}

void solve()
{
	dijkstra();

	for (int i{ 1 }; i <= N; ++i)
	{
		result = max(result, dist[i]);
	}

	cout << result * 2;
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