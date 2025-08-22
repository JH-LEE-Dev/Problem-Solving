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
using vertex = tuple<int, int, bool>;

#define MAX 100'001
#define endl '\n'
#define INF numeric_limits<int>::max()

int N{ 0 }, M{ 0 }, X{ 0 }, Y{ 0 }, Z{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<int>> dist(MAX, vector<int>(2, INF));

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
	}

	cin >> X >> Y >> Z;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,X,false });
	dist[X][false] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curState{ get<2>(cur) };

		if (dist[src][curState] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };
			auto newState{ curState };

			if (dst == Y)
				newState = true;

			if (dist[dst][newState] > newDist)
			{
				dist[dst][newState] = newDist;
				pq.push({ newDist,dst,newState });
			}
		}
	}
}

void solve()
{
	dijkstra();

	auto dist_1{ dist[Z][true] };
	auto dist_2{ dist[Z][false] };

	if (dist_1 == INF)
		cout << -1 << ' ';
	else
		cout << dist_1 << ' ';

	if (dist_2 == INF)
		cout << -1;
	else
		cout << dist_2;
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