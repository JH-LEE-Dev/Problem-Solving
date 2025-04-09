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
*	1. dist배열의 1차원을 정점, 2차원을 현재 뗏목의 두께로 설정하여 다익스트라 알고리즘을 실행.
*/

using namespace std;
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 2'001

int K, N, M;
int A, B;
vector<vector<tuple<int, int, int>>> edges(MAX, vector<tuple<int, int, int>>());
vector<vector<int>> dist(MAX, vector<int>(201, INF));

int result{ INF };

void input()
{
	cin >> K >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w, h;
		cin >> src >> dst >> w >> h;

		edges[src].push_back({ dst,w,h });
		edges[dst].push_back({ src,w,h });
	}

	cin >> A >> B;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,A,K });
	dist[A][K] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curH{ get<2>(cur) };

		if (dist[src][curH] < curDist)
			continue;

		if (src == B)
		{
			result = curDist;
			return;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ get<0>(edge) };
			auto w{ get<1>(edge) };
			auto h{ get<2>(edge) };
			auto newH{ curH - h };

			if (newH <= 0)
				continue;

			auto newDist{ curDist + w };

			if (dist[dst][newH] > newDist)
			{
				pq.push({ newDist,dst,newH });
				dist[dst][newH] = newDist;
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (result == INF)
		cout << -1;
	else
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