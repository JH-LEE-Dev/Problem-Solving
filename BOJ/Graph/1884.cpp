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
using edge = tuple<int, int, int>;
using vertex = tuple< int, int, int>;
#define MAX 101
#define endl '\n'
#define INF numeric_limits<int>::max()

int K, N, R;
vector<vector<edge>> edges(MAX, vector<edge>());
vector<vector<int>> dist(MAX, vector<int>(MAX* MAX, INF));

void input()
{
	cin >> K >> N >> R;

	for (int i{ 0 }; i < R; ++i)
	{
		int src, dst, w, t;
		cin >> src >> dst >> w >> t;

		edges[src].push_back({ dst,w,t });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0,1 });
	dist[1][0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<2>(cur) };
		auto curMoney{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src][curMoney] < curDist)
			continue;

		if (src == N)
		{
			cout << curDist;
			return;
		}

		for (auto& e : edges[src])
		{
			auto dst{ get<0>(e) };
			auto w{ get<1>(e) };
			auto t{ get<2>(e) };

			auto newDist{ curDist + w };
			auto newMoney{ curMoney + t };

			if (newMoney > K)
				continue;

			if (dist[dst][newMoney] > newDist)
			{
				dist[dst][newMoney] = newDist;
				pq.push({ newDist,newMoney,dst });
			}
		}
	}

	cout << -1;
}

void solve()
{
	dijkstra();
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