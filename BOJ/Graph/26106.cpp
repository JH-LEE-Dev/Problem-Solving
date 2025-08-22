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
using vertex = tuple<ll, tuple<int, int, int>>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 30'001

int N, M, K;
int start, goal;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
map<tuple<int, int, int>, ll> dist;

set<tuple<int, int, int>> kEdges;

ll result{ -1 };

void input()
{
	cin >> M >> N >> K;
	cin >> start >> goal;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int fir, sec, thr;

		cin >> fir >> sec >> thr;

		kEdges.insert({ fir,sec,thr });
	}
}

//연속된 특정 부분 경로를 2번 이용할 이유가 없기 때문에, dist의 차원으로 사용했다.
void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,{-1,-1,start} });
	dist[{-1, -1, start}] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		auto firstVertex{ get<1>(src) };
		auto secondVertex{ get<2>(src) };
		auto curVertex{ get<2>(src) };

		if (dist[src] < curDist)
			continue;

		if (curVertex == goal)
		{
			result = curDist;
			return;
		}

		int idx{ 0 };

		for (auto& edge : edges[curVertex])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (kEdges.find({ firstVertex,secondVertex,dst }) == kEdges.end())
			{
				if (dist.find({ firstVertex, secondVertex, dst }) == dist.end())
				{
					dist[{ firstVertex, secondVertex, dst }] = newDist;
					pq.push({ newDist,{ firstVertex,secondVertex,dst } });
				}
				else
				{
					if (dist[{ firstVertex, secondVertex, dst }] > newDist)
					{
						dist[{ firstVertex, secondVertex, dst }] = newDist;
						pq.push({ newDist,{ firstVertex,secondVertex,dst } });
					}
				}
			}
		}
	}
}

void solve()
{
	dijkstra();

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