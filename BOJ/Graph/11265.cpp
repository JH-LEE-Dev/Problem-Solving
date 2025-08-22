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
using q = tuple<int, int, int>;
using ll = long long;

#define MAX 501
#define endl '\n'
#define INF numeric_limits<ll>::max()/2

int N{ 0 }, Q{ 0 };
vector<vector<ll>> dist(MAX, vector<ll>(MAX, INF));
vector<q> query;

void input()
{
	cin >> N >> Q;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			cin >> dist[i][j];
		}
	}

	for (int i{ 0 }; i < Q; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };

		cin >> src >> dst >> w;
		query.push_back({ src,dst,w });
	}
}

void floydWarshall()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		dist[i][i] = 0;
	}

	for (int middle{ 1 }; middle <= N; ++middle)
	{
		for (int left{ 1 }; left <= N; ++left)
		{
			for (int right{ 1 }; right <= N; ++right)
			{
				dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
			}
		}
	}

	for (int i{ 0 }; i < Q; ++i)
	{
		auto src{ get<0>(query[i]) };
		auto dst{ get<1>(query[i]) };
		auto w{ get<2>(query[i]) };

		if (dist[src][dst] <= w)
		{
			cout << "Enjoy other party" << endl;
		}
		else
		{
			cout << "Stay here" << endl;
		}
	}
}

void solve()
{
	floydWarshall();
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