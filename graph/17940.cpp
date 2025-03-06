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
#define MAX 1'001

int N, goal;
vector<vector<int>> edges(MAX, vector<int>(MAX, INF));
vector<pair<int, int>> dist(MAX, { INF,INF });
vector<int> type(MAX, 0);

void input()
{
	cin >> N >> goal;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> type[i];
	}

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> edges[i][j];
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0,0 });
	dist[0] = make_pair(0, 0);

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<2>(cur) };
		auto curDist{ get<0>(cur) };
		auto curChange{ get<1>(cur) };

		if (dist[src] < make_pair(curChange, curDist))
			continue;

		for (int dst{ 0 }; dst < N; ++dst)
		{
			if (edges[src][dst] == 0)
				continue;

			auto w{ edges[src][dst] };
			auto newDist{ curDist + w };
			auto newChange{ curChange };

			if (type[dst] != type[src])
			{
				newChange += 1;
			}

			if (dist[dst] > make_pair(newChange, newDist))
			{
				dist[dst] = make_pair(newChange, newDist);
				pq.push({ newDist,newChange,dst });
			}
		}
	}
}

void solve()
{
	dijkstra();

	cout << dist[goal].first << ' ' << dist[goal].second;
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