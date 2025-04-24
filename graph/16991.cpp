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

#define endl '\n'
#define INF numeric_limits<double>::max()
#define MAX 16

int N, M;

vector<pair<int, int>> coords;
vector<vector<double>> dist(MAX, vector<double>(1 << MAX, -1));

pair<int, int> start;

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int src, dst;

		cin >> src >> dst;

		coords.push_back({ src,dst });
	}

	start.first = coords[0].first;
	start.second = coords[0].second;
}

double dfs(int v, int curBit)
{
	int x{ coords[v].first };
	int y{ coords[v].second };

	if (curBit == (1 << N) - 1)
	{
		double distance{ hypot(abs(x - start.first),abs(y - start.second)) };

		return distance;
	}

	if (dist[v][curBit] != -1)
		return dist[v][curBit];

	dist[v][curBit] = INF;

	for (int i{ 0 }; i < N; ++i)
	{
		if ((curBit & (1 << i)) == (1 << i))
			continue;

		int newBit{ curBit | (1 << i) };

		int dst_x{ coords[i].first };
		int dst_y{ coords[i].second };

		double distance{ hypot(abs(x - dst_x),abs(y - dst_y)) };

		dist[v][curBit] = min(dist[v][curBit], dfs(i, newBit) + distance);
	}

	return dist[v][curBit];
}

void solve()
{
	cout << fixed << setprecision(6) << dfs(0, 1);
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