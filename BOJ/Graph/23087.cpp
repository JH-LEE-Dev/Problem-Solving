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
using vertex = tuple<ll, ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 100'001
#define DIV 1'000'000'009

int N, M;
int start, goal;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<pair<ll, ll>> dist(MAX, { INF,INF });
vector<ll> cnt(MAX, 0);

void input()
{
	cin >> N >> M;
	cin >> start >> goal;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0,start });
	dist[start] = make_pair(0, 0);
	cnt[start] = 1;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<2>(cur) };
		auto curDist{ get<0>(cur) };
		auto curCnt{ get<1>(cur) };

		if (dist[src] < make_pair(curDist, curCnt))
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };
			auto newCnt{ curCnt + 1 };

			if (dist[dst] > make_pair(newDist, newCnt))
			{
				dist[dst] = make_pair(newDist, newCnt);
				pq.push({ newDist,newCnt,dst });

				cnt[dst] = cnt[src];
			}
			else if (dist[dst] == make_pair(newDist, newCnt))
			{
				cnt[dst] = (cnt[dst] + cnt[src]) % DIV;
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (dist[goal].first == INF)
		cout << -1;
	else
		cout << dist[goal].first << endl << dist[goal].second << endl << cnt[goal] % DIV;
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