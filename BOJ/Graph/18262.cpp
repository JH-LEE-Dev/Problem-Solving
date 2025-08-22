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
*	문제 해결 로직
*	1. 현재 존재하는 모든 유량에 대해서 다익스트라를 돌려본다. 즉 각 유량이 최소 유량이라고 가정하고 다익스트라를 실행한다.
	2. 다익스트라 알고리즘에서, 매개변수로 주어진 최소 유량보다 작은 유량을 가진 간선은 continue한다.
	3. 모든 유량에 대해 FJ를 계산해보고 최댓값을 구한다.
*/

using namespace std;
using vertex = tuple<int, int>;
#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int N, M;
int result{ 0 };
vector<int> flow;

vector<vector<tuple<int, int, int>>> edges(MAX, vector<tuple<int, int, int>>());
vector<int> dist(MAX, INF);

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, c, f;
		cin >> src >> dst >> c >> f;

		edges[src].push_back({ dst,c,f });
		edges[dst].push_back({ src,c,f });

		flow.push_back(f);
	}
}

void dijkstra(int minF)
{
	dist = vector<int>(MAX, INF);

	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,1 });
	dist[1] = 0;

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
			auto c{ get<1>(edge) };
			auto f{ get<2>(edge) };

			auto newDist{ curDist + c };

			if (f < minF)
				continue;

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}

	if (dist[N] == INF)
		return;

	int totalValue{ int(((double)minF / (double)dist[N]) * 1'000'000) };

	result = max(result, totalValue);
}

void solve()
{
	input();

	for (int i{ 0 }; i < flow.size(); ++i)
	{
		dijkstra(flow[i]);
	}

	cout << result;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}