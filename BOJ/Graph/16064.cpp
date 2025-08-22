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

/*
*	문제 해결 전략
*	1. 플로이드 워셜로 최대 비용을 구한다.
*
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()/2
#define MAX 1'001

int N, M;
int result{ -INF };
vector<vector<int>> dist(MAX, vector<int>(MAX, -INF));

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		if (dist[src][dst] != -INF)
			dist[src][dst] = max(dist[src][dst], w);
		else
			dist[src][dst] = w;
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
			if (dist[left][middle] == -INF)
				continue;

			for (int right{ 1 }; right <= N; ++right)
			{
				if (dist[middle][right] == -INF)
					continue;

				dist[left][right] = max(dist[left][right], dist[left][middle] + dist[middle][right]);

				result = max(result, dist[left][right]);
			}
		}
	}
}

void solve()
{
	floydWarshall();

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