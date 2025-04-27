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
*	1. 다익스트라 알고리즘을 사용한다. 거리 배열은 2차원이고 홀수와 짝수 거리를 나눠서 저장하기 위함이다.
*	2. 거리 배열을 홀수와 짝수로 나누는 이유는, 예를 들어 v번 정점에 홀수로 도달한 거리보다 짝수로 도달한 거리가 더 작으면, 홀수
*		경로는 pruning되어 짝수 경로만 살아남는다. v+1번 정점에 짝수 경로가 홀수 경로로 바뀌어 도달한다면, 짝수 경로를 계산할 수 없다.
*		즉 v번 정점에 거리는 더 길더라도 홀수로 올 수 있는 경로가 있어야 v+1번 정점에 짝수 경로를 계산할 수 있다.
*/

using namespace std;
using ll = long long;
using vertex = tuple<ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 100'001

int N, M;

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<ll>> dist(MAX, vector<ll>(2, INF));

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,1 });

	dist[1][0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src][curDist % 2] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst][newDist % 2] > newDist)
			{
				dist[dst][newDist % 2] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	dijkstra();

	for (int i{ 1 }; i <= N; ++i)
	{
		if (dist[i][1] == INF)
			cout << -1 << ' ';
		else
			cout << dist[i][1] << ' ';

		if (dist[i][0] == INF)
			cout << -1 << endl;
		else
			cout << dist[i][0] << endl;
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