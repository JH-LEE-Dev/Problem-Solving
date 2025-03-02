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
using vertex = tuple<ll, int, bool>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 100'001

int start, goal;
int N, M, P;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
set<int> v;
vector<vector<ll>>dist(MAX, vector<ll>(2, INF));

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

	cin >> P;

	for (int i{ 0 }; i < P; ++i)
	{
		int temp;
		cin >> temp;

		v.insert(temp);
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,start,false });
	dist[start][false] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curState{ get<2>(cur) };

		if (dist[src][curState] < curDist)
			continue;

		if (curState == true && src == goal)
			return;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + (ll)w };
			bool nxtState{ curState };

			if (v.find(dst) != v.end())
			{
				nxtState = true;
			}

			if (dist[dst][nxtState] > newDist)
			{
				dist[dst][nxtState] = newDist;
				pq.push({ newDist,dst,nxtState });
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (dist[goal][true] == INF)
		cout << -1;
	else
		cout << dist[goal][true];
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