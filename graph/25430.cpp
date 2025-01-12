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
using vertex = tuple<ll, int, int>;

#define MAX 50'001
#define endl '\n'
#define INF numeric_limits<ll>::max()
#define INF_INT numeric_limits<int>::max()

int N{ 0 }, M{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);
vector<int> prevWeight(MAX, INF_INT);
int start{ 0 }, goal{ 0 };

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	cin >> start >> goal;
}

void dijkstra(int start)
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,start,0 });
	dist[start] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto prevW{ get<2>(cur) };

		if (dist[src] < curDist && prevWeight[src] < prevW)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };

			if (w > prevW)
			{
				auto newDist{ curDist + w };

				if (dist[dst] > newDist)
				{
					dist[dst] = newDist;
					pq.push({ newDist,dst,w });

					if (prevWeight[dst] > w)
					{
						prevWeight[dst] = w;
					}
				}
				else if (prevWeight[dst] > w)
				{
					prevWeight[dst] = w;
					pq.push({ newDist,dst,w });
				}
			}
		}
	}
}

void solve()
{
	dijkstra(start);

	if (dist[goal] == INF)
		cout << "DIGESTA";
	else
		cout << dist[goal];
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}