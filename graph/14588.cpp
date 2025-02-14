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

#define MAX 301
#define endl '\n'
#define INF numeric_limits<int>::max()/2

int N{ 0 }, Q{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<pair<int, int>> query;
vector<pair<int, int>> lines;

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int src{ 0 }, dst{ 0 };
		cin >> src >> dst;

		lines.push_back({ src,dst });
	}

	cin >> Q;

	for (int i{ 0 }; i < Q; ++i)
	{
		int src{ 0 }, dst{ 0 };
		cin >> src >> dst;

		query.push_back({ src,dst });
	}
}

void generateGraph()
{
	for (int i{ 0 }; i < N; ++i)
	{
		auto src_start{ lines[i].first };
		auto src_end{ lines[i].second };

		for (int j{ 0 }; j < N; ++j)
		{
			if (i == j)
				continue;

			auto dst_start{ lines[j].first };
			auto dst_end{ lines[j].second };

			if ((src_start <= dst_end && dst_start <= src_end))
			{
				dist[i][j] = 1;
				dist[j][i] = 1;
			}
		}
	}
}

void floydWarshall()
{
	for (int i{ 0 }; i < N; ++i)
	{
		dist[i][i] = 0;
	}

	for (int middle{ 0 }; middle < N; ++middle)
	{
		for (int left{ 0 }; left < N; ++left)
		{
			for (int right{ 0 }; right < N; ++right)
			{
				dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
			}
		}
	}
}

void solve()
{
	generateGraph();

	floydWarshall();

	for (int i{ 0 }; i < Q; ++i)
	{
		auto src{ query[i].first - 1 };
		auto dst{ query[i].second - 1 };

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