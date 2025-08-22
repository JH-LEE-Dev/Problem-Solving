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
*	1. 모든 컴퓨터와 통신이 가능해야 하고, 평균 통신 시간이 가장 짧아야 하므로,
*		플로이드 워셜 알고리즘을 실행해서, 모든 컴퓨터에 도달 가능하고, 평균 통신 시간이
*		가장 짧은 컴퓨터를 답으로 제출.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()/2
#define MAX 201

int N, M;
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		dist[src][dst] = w;
		dist[dst][src] = w;
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

	int result{ INF };
	int minTime{ INF };

	for (int i{ 1 }; i <= N; ++i)
	{
		int curMinTime{ 0 };
		bool isValid{ true };

		for (int j{ 1 }; j <= N; ++j)
		{
			if (i == j)
				continue;

			if (dist[i][j] == INF)
			{
				isValid = false;
				break;
			}

			curMinTime += dist[i][j];

		}

		if (isValid)
		{
			if (curMinTime < minTime)
			{
				result = i;
				minTime = curMinTime;
			}
		}
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