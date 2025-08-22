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
using vertex = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int N, M;
int A, B, K, G;

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<int>> stopBy(MAX, vector<int>(MAX, INF));
vector<int> v;
vector<int> dist(MAX, INF);

void input()
{
	cin >> N >> M >> A >> B >> K >> G;

	for (int i{ 0 }; i < G; ++i)
	{
		int temp;

		cin >> temp;

		v.push_back(temp);
	}

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
	pq.push({ K,A });
	dist[A] = K;

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
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			auto stopTime{ stopBy[src][dst] };

			if (stopTime != INF)
			{
				auto endTime{ stopTime + w };

				if (curDist < stopTime || endTime <= curDist)
				{
					if (dist[dst] > newDist)
					{
						dist[dst] = newDist;
						pq.push({ newDist,dst });
					}
				}
				else
				{
					if (dist[dst] > endTime + w)
					{
						dist[dst] = endTime + w;
						pq.push({ endTime + w,dst });
					}
				}
			}
			else
			{
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
	int tempDist{ 0 };

	for (int i{ 1 }; i < G; ++i)
	{
		int src{ v[i - 1] };
		int dst{ v[i] };

		stopBy[src][dst] = tempDist;
		stopBy[dst][src] = tempDist;

		for (auto& edge : edges[src])
		{
			auto goal{ edge.first };

			if (goal != dst)
				continue;

			tempDist += edge.second;

			break;
		}
	}

	dijkstra();

	cout << dist[B] - K;
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