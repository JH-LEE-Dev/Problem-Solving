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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;
#define MAX 1'005

int N{ 0 }, M{ 0 }, start{ 0 }, goal{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist(MAX, INF);

void dijkstra(int start)
{
	dist[start] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> myPQ;
	myPQ.push({ 0,start });

	while (myPQ.empty() == false)
	{
		auto cur = myPQ.top();
		myPQ.pop();

		auto curVertex = cur.second;
		auto curDist = cur.first;

		if (dist[curVertex] < curDist)
			continue;

		for (auto& edge : edges[curVertex])
		{
			auto dst = edge.first;
			auto weight = edge.second;
			auto newDist = curDist + weight;

			if (newDist < dist[dst])
			{
				dist[dst] = newDist;
				myPQ.push({ newDist,dst });
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;
		edges[src].push_back({ dst,w });
	}

	cin >> start >> goal;

	dijkstra(start);

	cout << dist[goal];

	return 0;
}