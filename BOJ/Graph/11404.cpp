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

#define endl '\n'
using namespace std;

#define MAX 105
#define INF numeric_limits<int>::max()/2

vector<vector<int>> weight(MAX, vector<int>(MAX, INF));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int V{ 0 }, E{ 0 };
	cin >> V >> E;

	for (int i{ 0 }; i < E; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		weight[src][dst] = min(w, weight[src][dst]);
	}

	for (int i{ 1 }; i <= V; ++i)
	{
		for (int j{ 1 }; j <= V; ++j)
		{
			dist[i][j] = weight[i][j];
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
				}
			}
		}
	}

	for (int i{ 1 }; i <= V; ++i)
	{
		for (int j{ 1 }; j <= V; ++j)
		{
			if (dist[i][j] == INF)
				cout << 0 << " ";
			else
				cout << dist[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}