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
#define MAX 200'001

int N, M;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
unordered_set<int> notes;
vector<pair<ll, ll>> dist(MAX, { INF,INF });
vector<int> parent(MAX, -1);

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

	for (int i{ 0 }; i < N; ++i)
	{
		int temp;

		cin >> temp;

		if (temp == 1)
			notes.insert(i + 1);
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	if (notes.find(1) != notes.end())
		pq.push({ 0,-1,1 });
	else
		pq.push({ 0,0,1 });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<2>(cur) };
		auto curDist{ get<0>(cur) };
		auto cnt{ get<1>(cur) };

		if (dist[src] < make_pair(curDist, cnt))
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };
			auto newCnt{ cnt };

			if (notes.find(dst) != notes.end())
			{
				--newCnt;
			}

			if (dist[dst] > make_pair(newDist, newCnt))
			{
				dist[dst] = make_pair(newDist, newCnt);
				pq.push({ newDist,newCnt,dst });
				parent[dst] = src;
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (-dist[N].second != notes.size())
		cout << -1;
	else
	{
		stack<int> path;
		auto cursor{ N };

		while (cursor != 1)
		{
			path.push(cursor);

			cursor = parent[cursor];
		}

		path.push(1);

		cout << path.size() << endl;

		while (path.empty() == false)
		{
			cout << path.top() << ' ';

			path.pop();
		}
	}
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