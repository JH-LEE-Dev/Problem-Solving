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
using vertex = tuple<double, int>;

#define MAX 1'001
#define endl '\n'
#define INF numeric_limits<int>::max()

ll N{ 0 }, W{ 0 };
double M{ 0 };
vector<pair<int, int>> vertexes;
vector<vector<double>> edges(MAX, vector<double>(MAX, INF));

vector<double> dist(MAX, INF);

void input()
{
	cin >> N >> W >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		int row{ 0 }, col{ 0 };
		cin >> row >> col;

		vertexes.push_back({ row,col });
	}

	for (int i{ 0 }; i < W; ++i)
	{
		int src{ 0 }, dst{ 0 };
		cin >> src >> dst;

		edges[src - 1][dst - 1] = 0;
		edges[dst - 1][src - 1] = 0;
	}

	for (int i{ 0 }; i < vertexes.size(); ++i)
	{
		for (int j{ 0 }; j < vertexes.size(); ++j)
		{
			if (i == j)
				continue;

			auto src{ vertexes[i] };
			auto dst{ vertexes[j] };

			auto r{ src.first };
			auto c{ src.second };
			auto dst_r{ dst.first };
			auto dst_c{ dst.second };

			double w{ 0 };

			if (edges[i][j] != 0)
			{
				w = hypot(abs(r - dst_r), abs(c - dst_c));

				if (w > M)
					continue;

				edges[i][j] = w;
				edges[j][i] = w;
			}
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
		auto r{ vertexes[src].first };
		auto c{ vertexes[src].second };

		if (dist[src] < curDist)
			continue;

		for (int i{ 0 }; i < vertexes.size(); ++i)
		{
			if (i == src)
				continue;

			auto dst{ vertexes[i] };

			double w{ edges[src][i] };

			auto newDist{ curDist + w };

			if (dist[i] > newDist)
			{
				dist[i] = newDist;
				pq.push({ newDist,i });
			}
		}
	}
}

void solve()
{
	dijkstra();

	cout << (ll)(dist[N - 1] * 1000);
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