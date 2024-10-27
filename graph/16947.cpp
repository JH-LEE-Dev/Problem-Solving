#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>

#define endl '\n'
using namespace std;

#define MAX 3'005

vector<int> e_dist(MAX, 0);
vector<vector<int>> edges(MAX, vector<int>());
vector<bool> visited(MAX, false);
vector<int> parent(MAX, 0);
unordered_set<int> cycle;

int cycleStart{ 0 }, cycleEnd{ 0 };

bool found{ false };

void findCycle(int from, int cur)
{
	visited[cur] = true;
	parent[cur] = from;

	for (auto& it : edges[cur])
	{
		if (it == 0)
			continue;

		if (found == true)
		{
			return;
		}

		if (it != from)
		{
			if (visited[it] == false)
				findCycle(cur, it);
			else
			{
				cycleStart = it;
				cycleEnd = cur;
				found = true;
				break;
			}
		}
	}

	if (found == true)
	{
		int cursor{ cycleEnd };

		while (1)
		{
			cycle.insert(cursor);
			cursor = parent[cursor];

			if (cycleStart == cursor)
			{
				cycle.insert(cursor);
				break;
			}
		}
	}
}

void bfs()
{
	visited = vector<bool>(MAX, false);
	queue<int> myQ;
	myQ.push(*cycle.begin());

	visited[myQ.front()] = true;

	while (!myQ.empty())
	{
		int cur = myQ.front();
		myQ.pop();

		for (auto& it : edges[cur])
		{
			if (it == 0)
				continue;

			if (visited[it] == true)
				continue;

			myQ.push(it);
			visited[it] = true;

			if (cycle.find(it) == cycle.end())
			{
				e_dist[it] = e_dist[cur] + 1;
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 };
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		int src{ 0 }, dst{ 0 };
		cin >> src >> dst;
		edges[src].push_back(dst);
		edges[dst].push_back(src);
	}

	findCycle(1, 1);
	bfs();

	for (int i{ 1 }; i <= N; ++i)
	{
		cout << e_dist[i] << " ";
	}

	return 0;
}