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

#define MAX 21
#define endl '\n'
#define INF numeric_limits<int>::max()

int T{ 0 }, N{ 0 }, M{ 0 };
vector<vector<pair<int, int>>> edges;
vector<int> parent;
vector<int> dist;

void input()
{
	cin >> T;
}

void testInput()
{
	edges = vector<vector<pair<int, int>>>(MAX, vector<pair<int, int>>());
	parent = vector<int>(MAX, -1);
	dist = vector<int>(MAX, INF);

	cin >> M >> N;

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
				dist[dst] = newDist;
				pq.push({ newDist,dst });
				parent[dst] = src;
			}
		}
	}
}

void solve()
{
	for (int i{ 0 }; i < T; ++i)
	{
		testInput();
		dijkstra();

		cout << "Case #" << i + 1 << ": ";

		if (dist[N - 1] == INF)
		{
			cout << -1 << endl;
			continue;
		}

		stack<int> result;
		auto cursor{ N - 1 };
		while (cursor != -1)
		{
			result.push(cursor);
			cursor = parent[cursor];
		}

		while (result.empty() == false)
		{
			cout << result.top() << ' ';
			result.pop();
		}

		cout << endl;
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