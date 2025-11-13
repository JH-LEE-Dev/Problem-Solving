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
using state = tuple<ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 1'000'001

int n, m;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<pair<int, int>>> edges_rev(MAX, vector<pair<int, int>>());
vector<ll> arr;
int s, t;
vector<ll> dist(MAX, INF);
ll result{ INF };
vector<ll> dp(MAX, -1);

void Input()
{
	cin >> n >> m;

	for (int i{ 0 }; i < n; ++i)
	{
		int temp;
		cin >> temp;

		arr.push_back(temp);
	}

	cin >> s >> t;

	for (int i{ 0 }; i < m; ++i)
	{
		int src, dst, w;
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges_rev[dst].push_back({ src,w });
	}
}

void dijkstra()
{
	priority_queue<state, vector<state>, greater<state>> pq;
	pq.push({ 0,s });
	dist[s] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto [curDist, src] {cur};

		if (dist[src] < curDist)
			continue;

		for (const auto& edge : edges[src])
		{
			auto [dst, w] {edge};
			auto newDist{ curDist + w };

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

ll dfs(int src)
{
	if (src == s)
		return arr[src - 1];

	if (dp[src] != -1)
		return dp[src];

	dp[src] = INF;

	for (const auto& edge : edges_rev[src])
	{
		auto [dst, w] {edge};

		if (dist[dst] + w == dist[src])
		{
			dp[src] = min(dfs(dst), dp[src]);
		}
	}

	result = min(dp[src] + arr[src - 1], result);

	return min(dp[src], arr[src - 1]);
}

void Solve()
{
	dijkstra();

	if (dist[t] == INF)
		cout << -1;
	else
	{
		dfs(t);
		cout << result;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();

	return 0;
}