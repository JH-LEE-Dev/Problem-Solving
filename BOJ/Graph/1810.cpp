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
* 1.각 징검다리를 정점으로한 그래프에서 다익스트라 알고리즘으로 거리를 구함.
*	- 시작점은 0,0
*	- 두 정점 사이의 좌표 차이가 2 이하인 정점들로만 이동할 수 있음.
*	- 거리는 두 좌표 차이의 제곱의 합
* 2.다익스트라 알고리즘 과정에서 y좌표가 결승선에 도달한다면, min함수로 최솟값을 비교하며 구함.
*
* 3.정점 개수가 매우 크기 때문에, 그래프를 생성하기에는 반복 수가 매우 많아져 시간 초과에 걸리므로
*	다익스트라 과정에서 x,y좌표 차이가 2 이하인 정점들을 찾아야 함.
*		- 이를 위해서 정점 배열을 y좌표를 1차원으로 설정, 2차원은 x좌표, 3차원은 정점 인덱스로 설정.
*		- 다익스트라 과정에서 이분 탐색을 활용하여 y좌표 -2 ~ +2 범위에서 x좌표 차이가 2인 정점들을 빠르게 탐색.
*/
using namespace std;
using vertex = tuple<double, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'000'000

int N, F;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<pair<int, int>> vertexes;
vector<double> dist(50'001, (double)INF);

double result{ (double)numeric_limits<int>::max() };

void input()
{
	cin >> N >> F;

	edges[0].push_back({ 0,0 });
	vertexes.push_back({ 0,0 });

	for (int i{ 1 }; i <= N; ++i)
	{
		int x, y;
		cin >> x >> y;

		edges[y].push_back({ x,i });
		vertexes.push_back({ x,y });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0 });
	dist[0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		auto curX{ vertexes[src].first };
		auto curY{ vertexes[src].second };

		if (curY >= F)
		{
			result = curDist;
			return;
		}

		for (int i{ -2 }; i < 3; ++i)
		{
			if (curY + i < 0 || curY + i > MAX)
				continue;

			auto left{ lower_bound(edges[curY + i].begin(), edges[curY + i].end(), make_pair(curX - 2,-1)) };
			auto right{ upper_bound(edges[curY + i].begin(),edges[curY + i].end(),make_pair(curX + 2,INF)) };

			auto leftIdx{ left - edges[curY + i].begin() };
			auto rightIdx{ right - edges[curY + i].begin() };

			for (int j{ (int)leftIdx }; j < rightIdx; ++j)
			{
				auto dst{ edges[curY + i][j].second };
				auto coord_dst{ vertexes[dst] };
				auto dst_x{ coord_dst.first };
				auto dst_y{ coord_dst.second };

				auto deltaX{ abs(curX - dst_x) };
				auto deltaY{ abs(curY - dst_y) };

				auto distance{ hypot(deltaX,deltaY) };

				auto newDist{ curDist + distance };

				if (dist[dst] > newDist)
				{
					dist[dst] = newDist;
					pq.push({ newDist,dst });
				}
			}
		}
	}
}

void solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		sort(edges[i].begin(), edges[i].end());
	}

	dijkstra();

	if (result == INF)
		cout << -1;
	else
		cout << (int)round(result);
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