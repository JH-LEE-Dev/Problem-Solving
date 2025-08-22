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
#define MAX 101

int N, T, M, L;
vector<vector<pair<int, pair<int, int>>>> edges(MAX, vector<pair<int, pair<int, int>>>());
vector<vector<int>> dist(MAX, vector<int>(10'001, INF));

int result{ INF };

void input()
{
	cin >> N >> T >> M >> L;

	for (int i{ 0 }; i < L; ++i)
	{
		int src, dst, time, money;

		cin >> src >> dst >> time >> money;

		edges[src].push_back({ dst,{time,money} });
		edges[dst].push_back({ src,{time,money} });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0,1 });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<2>(cur) };
		auto curMoney{ get<0>(cur) };
		auto curTime{ get<1>(cur) };

		if (dist[src][curTime] < curMoney)
		{
			continue;
		}

		if (src == N)
		{
			result = curMoney;
			return;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto time{ edge.second.first };
			auto money{ edge.second.second };

			auto newMoney{ curMoney + money };
			auto newTime{ curTime + time };

			if (newTime > T)
				continue;

			if (newMoney > M)
				continue;


			if (dist[dst][newTime] > newMoney)
			{
				dist[dst][newTime] = newMoney;
				pq.push({ newMoney,newTime,dst });
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