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
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'002

int N, M;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<pair<int, int>>> dist(MAX, vector<pair<int, int>>(6, { INF,INF }));

int result{ INF };

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
	pq.push({ 0,-100,0 });
	dist[0][0] = { 0,100 };

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<2>(cur) };
		auto curDist{ get<0>(cur) };
		auto curRemain{ -get<1>(cur) };

		if (dist[src][curDist % 5] < make_pair(curDist, curRemain))
			continue;

		if (src == N + 1)
		{
			result = curDist;
			return;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newRemain{ curRemain - w };

			if (w > 100)
				continue;

			if (newRemain < 0)
			{
				if (src > N)
					continue;

				newRemain = 100 - w;

				w += 5;
			}

			auto newDist{ curDist + w };

			if (dist[dst][newDist % 5] > make_pair(newDist, newRemain))
			{
				dist[dst][newDist % 5] = make_pair(newDist, newRemain);
				pq.push({ newDist,-newRemain,dst });
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