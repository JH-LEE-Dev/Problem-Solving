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

#define endl '\n'
#define INF numeric_limits<long long>::max()/2
using namespace std;
#define MAX 501

int T{ 0 }, N{ 0 }, M{ 0 }, W{ 0 };
vector<tuple<int, int, int>> edges;

vector<long long> dist(MAX, INF);
bool result{ false };

auto bellmanford()
{
	for (int i{ 0 }; i < N - 1; ++i)
	{
		for (auto& edge : edges)
		{
			int src = get<0>(edge);
			int dst = get<1>(edge);
			int w = get<2>(edge);

			if (dist[dst] > dist[src] + w)
				dist[dst] = dist[src] + w;
		}
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		for (auto& edge : edges)
		{
			int src = get<0>(edge);
			int dst = get<1>(edge);
			int w = get<2>(edge);

			if (dist[dst] > dist[src] + w)
			{
				cout << "YES" << endl;
				return;
			}
		}
	}

	cout << "NO" << endl;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> T;

	while (T != 0)
	{
		edges = vector<tuple<int, int, int>>();

		cin >> N >> M >> W;

		for (int i{ 0 }; i < M; ++i)
		{
			int src{ 0 }, dst{ 0 }, w{ 0 };
			cin >> src >> dst >> w;

			edges.push_back({ src,dst,w });
			edges.push_back({ dst,src,w });
		}

		for (int i{ 0 }; i < W; ++i)
		{
			int src{ 0 }, dst{ 0 }, w{ 0 };
			cin >> src >> dst >> w;

			edges.push_back({ src,dst,-w });
		}

		bellmanford();

		--T;
	}

	return 0;
}