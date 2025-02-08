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

#define MAX 11
#define MAX_MONEY 10'001
#define endl '\n'
#define INF numeric_limits<int>::max()

int N{ 0 }, M{ 0 }, A{ 0 }, B{ 0 }, C{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<int>> dist(MAX, vector<int>(MAX_MONEY, -1));

int result{ -1 };

void input()
{
	cin >> N >> M >> A >> B >> C;

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
	pq.push({ 0,A,0 });
	dist[A][0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curMax{ get<0>(cur) };
		auto curDist{ get<2>(cur) };

		if (dist[src][curDist] > curMax)
			continue;

		if (src == B)
		{
			result = curMax;
			return;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };
			auto tempMax = max(curMax, w);

			if (newDist > C)
				continue;

			if (dist[dst][newDist] < tempMax)
			{
				dist[dst][newDist] = tempMax;
				pq.push({ tempMax,dst,newDist });
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (result == INF)
		cout << -1;
	else
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