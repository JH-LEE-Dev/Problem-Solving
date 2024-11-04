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

#define MAX 105

vector<vector<int>> weight(MAX, vector<int>(MAX, INF));
int V{ 0 }, E{ 0 };
vector<vector<long long>> dist(MAX, vector<long long>(MAX, INF));
vector<vector<int>> parent(MAX, vector<int>(MAX, 0));

void floyd()
{
	for (int i{ 1 }; i <= V; ++i)
	{
		for (int j{ 1 }; j <= V; ++j)
		{
			dist[i][j] = weight[i][j];

			if (dist[i][j] != INF)
				parent[i][j] = i;
		}

		dist[i][i] = 0;
	}

	for (int mid{ 1 }; mid <= V; ++mid)
	{
		for (int left{ 1 }; left <= V; ++left)
		{
			for (int right{ 1 }; right <= V; ++right)
			{
				if (dist[left][mid] + dist[mid][right] < dist[left][right])
				{
					dist[left][right] = dist[left][mid] + dist[mid][right];
					parent[left][right] = parent[mid][right];
				}
			}
		}
	}

	for (int i{ 1 }; i <= V; ++i)
	{
		for (int j{ 1 }; j <= V; ++j)
		{
			if (dist[i][j] != INF)
				cout << dist[i][j] << " ";
			else
				cout << 0 << " ";
		}
		cout << endl;
	}

	for (int i{ 1 }; i <= V; ++i)
	{
		for (int j{ 1 }; j <= V; ++j)
		{
			if (i == j || dist[i][j] == INF)
			{
				cout << 0 << endl;
				continue;
			}

			stack<int> path;
			auto cursor = j;
			while (cursor != i)
			{
				path.push(cursor);
				cursor = parent[i][cursor];
			}
			path.push(i);

			cout << path.size() << " ";

			while (path.empty() == false)
			{
				cout << path.top() << " ";
				path.pop();
			}
			cout << endl;
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> V >> E;

	for (int i{ 0 }; i < E; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;
		weight[src][dst] = min(weight[src][dst], w);
	}

	floyd();

	return 0;
}