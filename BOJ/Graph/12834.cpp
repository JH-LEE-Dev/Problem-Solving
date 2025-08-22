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

#define MAX 1'001
#define endl '\n'
#define INF numeric_limits<int>::max()/2

int N{ 0 }, V{ 0 }, E{ 0 }, A{ 0 }, B{ 0 };
vector<int> knights;
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

void input()
{
	cin >> N >> V >> E >> A >> B;

	for (int i{ 0 }; i < N; ++i)
	{
		int temp{ 0 };
		cin >> temp;

		knights.push_back(temp);
	}

	for (int i{ 0 }; i < E; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		dist[src][dst] = w;
		dist[dst][src] = w;
	}
}

void floydWarshall()
{
	for (int i{ 1 }; i <= V; ++i)
	{
		dist[i][i] = 0;
	}

	for (int middle{ 1 }; middle <= V; ++middle)
	{
		for (int left{ 1 }; left <= V; ++left)
		{
			for (int right{ 1 }; right <= V; ++right)
			{
				dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
			}
		}
	}
}

void solve()
{
	floydWarshall();

	int result{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		if (dist[knights[i]][A] == INF)
			result += -1;
		else
			result += dist[knights[i]][A];

		if (dist[knights[i]][B] == INF)
			result += -1;
		else
			result += dist[knights[i]][B];
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