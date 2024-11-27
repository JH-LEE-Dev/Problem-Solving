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
#define INF numeric_limits<long long>::max()
using namespace std;
#define MAX 101
vector<tuple<int, int, int>> edges;
int N{ 0 }, M{ 0 };
vector<long long> dist(MAX, -INF);
vector<int> parent(MAX, -1);
vector<int> visited(MAX, false);

void bfs(int start)
{
	queue<int> myQ;
	myQ.push(start);

	visited[start] = true;

	while (myQ.empty() == false)
	{
		auto cur = myQ.front();
		myQ.pop();

		for (auto& edge : edges)
		{
			int src = get<0>(edge);
			int dst = get<1>(edge);

			if (src == cur && visited[dst] == false)
			{
				visited[dst] = true;
				myQ.push(dst);
			}
		}
	}
}

void bellmanford()
{
	bool hasCycle{ false };
	unordered_set<int> cycle;

	dist[1] = 0;

	for (int i{ 0 }; i < N; ++i)
	{
		for (auto& edge : edges)
		{
			int src = get<0>(edge);
			int dst = get<1>(edge);
			int w = get<2>(edge);

			if (dist[src] == -INF)
				continue;

			if (dist[dst] < dist[src] + w)
			{
				if (i != N - 1)
				{
					dist[dst] = dist[src] + w;
					parent[dst] = src;
				}
				else
				{
					bfs(dst);

					if (visited[N] == true)
					{
						cout << -1;
						return;
					}
				}
			}
		}
	}

	if (dist[N] == -INF)
	{
		cout << -1;
		return;
	}

	stack<int> path;
	int cursor = N;

	while (cursor != -1)
	{
		path.push(cursor);
		cursor = parent[cursor];
	}

	while (path.empty() == false)
	{
		cout << path.top() << " ";
		path.pop();
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;
	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;
		cin >> src >> dst >> w;
		edges.push_back({ src,dst,w });
	}

	bellmanford();

	return 0;
}