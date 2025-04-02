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
#define MAX 5'001

int N, M;
int P, Q;

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist(MAX, INF);
set<int> ministop;
vector<int> home;
pair<int, int> minResult{ INF,INF };

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

	cin >> P >> Q;

	for (int i{ 0 }; i < P; ++i)
	{
		int temp;
		cin >> temp;

		home.push_back(temp);
	}

	for (int i{ 0 }; i < Q; ++i)
	{
		int temp;
		cin >> temp;

		ministop.insert(temp);
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	for (int i{ 0 }; i < P; ++i)
	{
		pq.push({ 0,home[i],home[i] });
		dist[home[i]] = 0;
	}

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto fromHome{ get<2>(cur) };

		if (dist[src] < curDist)
			continue;

		if (ministop.find(src) != ministop.end())
		{
			auto curResult = make_pair(curDist, fromHome);

			if (minResult > curResult)
			{
				minResult = curResult;
			}
		}

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst,fromHome });
			}
		}
	}
}

void solve()
{
	dijkstra();

	cout << minResult.second;
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