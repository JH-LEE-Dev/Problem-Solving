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

using vertex = tuple<ll, ll>;

#define MAX 1'001
#define endl '\n'
#define INF numeric_limits<ll>::max()

vector<pair<ll, ll>> vertexes;
vector<vector<pair<ll, ll>>> edges(MAX, vector<pair<ll, ll>>());
vector<ll> dist(MAX, INF);

pair<ll, ll> start;
pair<ll, ll> goal;

void input()
{
	cin >> start.first >> start.second;
	cin >> goal.first >> goal.second;

	vertexes.push_back(start);

	for (int i{ 0 }; i < 3; ++i)
	{
		int s_r{ 0 }, s_c{ 0 }, d_r{ 0 }, d_c{ 0 };
		cin >> s_r >> s_c >> d_r >> d_c;

		vertexes.push_back({ s_r,s_c });
		vertexes.push_back({ d_r,d_c });

		int idx{ (int)vertexes.size() - 2 };

		edges[idx].push_back({ idx + 1,10 });
		edges[idx + 1].push_back({ idx,10 });
	}

	vertexes.push_back(goal);
}

void generateGraph()
{
	for (int i{ 0 }; i < vertexes.size(); ++i)
	{
		for (int j{ 0 }; j < vertexes.size(); ++j)
		{
			if (i == j)
				continue;

			auto src{ vertexes[i] };
			auto dst{ vertexes[j] };
			auto w{ abs(src.first - dst.first) + abs(src.second - dst.second) };

			edges[i].push_back({ j,w });
			edges[j].push_back({ i,w });
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0 });
	dist[0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		for (auto& edge : edges[src])
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

	cout << dist[vertexes.size() - 1];
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