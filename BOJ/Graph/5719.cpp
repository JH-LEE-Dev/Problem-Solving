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
int N{ 0 }, M{ 0 }, start{ 0 }, goal{ 0 };
#define MAX 505

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<pair<int, int>>> parent(MAX, vector<pair<int, int>>());
vector<vector<bool>> shortest_path(MAX, vector<bool>(MAX, false));
vector<int> dist(MAX, INF);

void tracePath(int cursor, int src)
{
	if (cursor == start)
	{
		shortest_path[cursor][src] = true;
		return;
	}

	shortest_path[cursor][src] = true;

	for (auto& dst : parent[cursor])
	{
		if (dst.second == dist[cursor] && shortest_path[dst.first][cursor] == false)
		{
			tracePath(dst.first, cursor);
		}
	}
}

void dijkstra_shortest()
{
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

			if (dist[dst] == newDist)
			{
				parent[dst].push_back({ curVertex,newDist });
				continue;
			}

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				myPQ.push({ newDist,dst });
				parent[dst].push_back({ curVertex,newDist });
			}
		}
	}

	for (auto& dst : parent[goal])
	{
		if (dst.second == dist[goal])
			tracePath(dst.first, goal);
	}
}

void dijkstra_second_shortest()
{
	vector<int> dist_second(MAX, INF);

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> myPQ;
	myPQ.push({ 0,start });

	while (myPQ.empty() == false)
	{
		auto cur = myPQ.top();
		myPQ.pop();
		auto curVertex = cur.second;
		auto curDist = cur.first;

		if (dist_second[curVertex] < curDist)
			continue;

		for (auto& edge : edges[curVertex])
		{
			auto dst = edge.first;
			auto weight = edge.second;
			auto newDist = curDist + weight;

			if (dist_second[dst] > newDist && shortest_path[curVertex][dst] == false)
			{
				dist_second[dst] = newDist;
				myPQ.push({ newDist,dst });
			}
		}
	}

	if (dist_second[goal] == INF)
		cout << -1 << endl;
	else
		cout << dist_second[goal] << endl;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	while (1)
	{
		cin >> N >> M;

		if (N == 0 && M == 0)
			break;

		cin >> start >> goal;

		edges = vector<vector<pair<int, int>>>(MAX, vector<pair<int, int>>());
		parent = vector<vector<pair<int, int>>>(MAX, vector<pair<int, int>>());
		shortest_path = vector<vector<bool>>(MAX, vector<bool>(MAX, false));
		dist = vector<int>(MAX, INF);

		for (int i{ 0 }; i < M; ++i)
		{
			int src{ 0 }, dst{ 0 }, w{ 0 };
			cin >> src >> dst >> w;

			edges[src].push_back({ dst,w });
		}

		dijkstra_shortest();
		dijkstra_second_shortest();
	}

	return 0;
}