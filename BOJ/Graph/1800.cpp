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

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 1'001

int N{ 0 }, M{ 0 }, K{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<ll>> dist(MAX, vector<ll>(MAX, INF));

int result{ 0 };

void input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,1,0 });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto curDist{ get<0>(cur) };
		auto src{ get<1>(cur) };
		auto cnt{ get<2>(cur) };

		if (dist[src][cnt] < curDist)
			continue;

		if (src == N)
		{
			result = curDist;
			return;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };

			if (cnt < K)
			{
				if (dist[dst][cnt + 1] > curDist)
				{
					dist[dst][cnt + 1] = curDist;
					pq.push({ curDist,dst,cnt + 1 });
				}
			}

			auto curMax{ curDist };
			curMax = max(curMax, (ll)w);

			if (dist[dst][cnt] > curMax)
			{
				dist[dst][cnt] = curMax;
				pq.push({ curMax,dst,cnt });
			}
		}
	}

	result = -1;
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