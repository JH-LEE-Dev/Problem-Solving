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
using ll = long long;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 301

int N, M, T;

vector<vector<ll>> dist(MAX, vector<ll>(MAX, INF));
vector<pair<int, int>> jobs;

void input()
{
	cin >> N >> M >> T;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		dist[src][dst] = w;
	}

	for (int i{ 0 }; i < T; ++i)
	{
		int src, dst;

		cin >> src >> dst;

		jobs.push_back({ src,dst });
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
				dist[left][right] = min(dist[left][right], max(dist[left][middle], dist[middle][right]));
			}
		}
	}
}

void solve()
{
	floydWarshall();

	for (int i{ 0 }; i < T; ++i)
	{
		int src{ jobs[i].first };
		int dst{ jobs[i].second };

		if (dist[src][dst] == INF)
			cout << -1 << endl;
		else
			cout << dist[src][dst] << endl;
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