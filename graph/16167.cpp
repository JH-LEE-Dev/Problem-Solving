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
*	1. dist배열을 pair로 설정한다. first는 거리, second는 거친 경로의 수. 따라서 최단 경로가 우선 평가되고,
*	   같은 거리일 때는, 정점을 더 적게 방문한 경로가 통과한다.
*	2. 요금은 10분간 기본 요금, 이후 시간은 추가 요금이 부과된다.
*/

using namespace std;
using vertex = tuple<pair<int, int>, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 201

int N, M;
vector<vector<tuple<int, int, int, int>>> edges(MAX, vector<tuple<int, int, int, int>>());
vector<pair<int, int>> dist(MAX, { INF,INF });

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w1, w2, t;
		cin >> src >> dst >> w1 >> w2 >> t;

		edges[src].push_back({ dst,w1,w2,t });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ {0,1},1 });
	dist[1] = make_pair(0, 1);

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ get<0>(edge) };
			auto w1{ get<1>(edge) };
			auto w2{ get<2>(edge) };
			auto t{ get<3>(edge) };

			pair<int, int> newDist{ curDist.first + w1,curDist.second + 1 };

			if (t > 10)
			{
				newDist.first += (t - 10) * w2;
			}

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (dist[N].first == INF)
	{
		cout << "It is not a great way.";
		return;
	}

	cout << dist[N].first << ' ' << dist[N].second;
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