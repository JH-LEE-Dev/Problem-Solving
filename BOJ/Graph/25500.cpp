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

#define MAX 200'001
#define endl '\n'
#define INF numeric_limits<long long>::max()
using namespace std;
int N{ 0 }, K{ 0 };
using edge = tuple<int, int, int, int>;
vector<edge> edges(MAX);
vector <vector<pair<int, int>>> graph(2 * MAX, vector<pair<int, int>>());
using ll = long long;
using vertex = tuple<ll, int>;
vector<ll>dist(2 * MAX, INF);

void input()
{
	cin >> N >> K;

	for (int i{ 1 }; i <= N; ++i)
	{
		int x, y, z;
		cin >> x >> y >> z;

		edges[i] = { x,y,z,i };

		auto remainder_1{ z % K };
		auto remainder_2{ (K - remainder_1) % K };

		graph[i].push_back({ N + 1 + remainder_1,z });
		graph[N + 1 + remainder_2].push_back({ i,z });
	}
}

void generateGraph()
{
	sort(edges.begin() + 1, edges.begin() + N + 1);

	for (int i{ 2 }; i <= N; ++i)
	{
		auto src{ get<3>(edges[i]) };
		auto dst{ get<3>(edges[i - 1]) };
		auto w{ abs(get<0>(edges[i]) - get<0>(edges[i - 1])) };

		graph[src].push_back({ dst,w });
		graph[dst].push_back({ src,w });
	}

	sort(edges.begin() + 1, edges.begin() + N + 1, [](const edge& lhs, const edge& rhs) {
		return get<1>(lhs) < get<1>(rhs);
		});

	for (int i{ 2 }; i <= N; ++i)
	{
		auto src{ get<3>(edges[i]) };
		auto dst{ get<3>(edges[i - 1]) };
		auto w{ abs(get<1>(edges[i]) - get<1>(edges[i - 1])) };

		graph[src].push_back({ dst,w });
		graph[dst].push_back({ src,w });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,1 });
	dist[1] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto curDist{ get<0>(cur) };
		auto src{ get<1>(cur) };

		if (dist[src] < curDist)
			continue;

		for (auto& edge : graph[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	generateGraph();
	dijkstra();

	for (int i{ 1 }; i <= N; ++i)
	{
		cout << dist[i] << endl;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}