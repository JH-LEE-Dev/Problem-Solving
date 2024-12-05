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

#define endl '\n'
#define INF numeric_limits<int>::max()/2
using namespace std;
#define MAX 301

vector<vector<int>> weight(MAX, vector<int>(MAX, INF));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(MAX, INF)));

int N{ 0 }, T{ 0 };

void floydWarshall()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			dist[i][j][0] = weight[i][j];
		}

		dist[i][i][0] = 0;
	}

	//이 문제는, C 이하의 정점들만 방문해야 한다.
	//dist[left][right][middle]의 의미는 left에서 right로 갈 때에 middle까지 경우했을 때 최단 거리이다.
	//for loop에서 middle이 1에서 N까지 선형적으로 상승하므로 middle-1 까지 경유했을 경우와 비교한다. 

	//일반적인 Floyd - Warshall 알고리즘과 구하는 값의 차이는 없다. dist[left][right][N]의 경우가 left에서 right로 가는 절대적 최단 거리이다.
	//하지만 C이하의 정점들만 방문했을 때의 거리를 알아야 하므로(left,right가 C 이상인 경우는 제외된다. 즉 중간 경로만 C 이하이면 된다.)
	//3차원 DP를 사용한다.
	for (int middle{ 1 }; middle <= N; ++middle)
	{
		for (int left{ 1 }; left <= N; ++left)
		{
			for (int right{ 1 }; right <= N; ++right)
			{
				dist[left][right][middle] = min(dist[left][right][middle - 1], dist[left][middle][middle - 1] + dist[middle][right][middle - 1]);
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> T;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			cin >> weight[i][j];

			if (weight[i][j] == 0)
				weight[i][j] = INF;
		}
	}

	floydWarshall();

	while (T != 0)
	{
		int C{ 0 }, start{ 0 }, goal{ 0 };
		cin >> C >> start >> goal;

		if (dist[start][goal][C - 1] != INF)
			cout << dist[start][goal][C - 1] << endl;
		else
			cout << -1 << endl;

		--T;
	}

	return 0;
}