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

#define endl '\n'
#define INF numeric_limits<int>::max()/2
#define MAX 257

int N, M;
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst;

		cin >> src >> dst;

		dist[src][dst] = 1;
	}
}

void floydWarshall()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		dist[i][i] = 0;
	}

	for (int middle{ 1 }; middle <= N; ++middle)
	{
		for (int left{ 1 }; left <= N; ++left)
		{
			for (int right{ 1 }; right <= N; ++right)
			{
				dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
			}
		}
	}
}

void solve()
{
	floydWarshall();

	vector<pair<int, int>> result;

	for (int i{ 1 }; i <= N; ++i)
	{
		int indegrees{ 0 };
		int outdegrees{ 0 };

		for (int j{ 1 }; j <= N; ++j)
		{
			if (i == j)
				continue;

			if (dist[i][j] != INF)
				++outdegrees;

			if (dist[j][i] != INF)
				++indegrees;

			if (dist[i][j] != INF && dist[j][i] != INF)
			{
				cout << -1;
				return;
			}
		}

		result.push_back({ 1 + indegrees,N - outdegrees });
	}

	for (int i{ 0 }; i < N; ++i)
	{
		cout << result[i].first << ' ' << result[i].second << endl;
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