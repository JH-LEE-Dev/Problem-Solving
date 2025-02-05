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
#define INF numeric_limits<int>::max()/2
#define MAX 1'001

int N{ 0 }, T{ 0 }, Q{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<pair<int, pair<int, int>>> vertexes;
vector<pair<int, int>> query;

void input()
{
	cin >> N >> T;

	for (int i{ 0 }; i < N; ++i)
	{
		int type{ 0 }, row{ 0 }, col{ 0 };

		cin >> type >> row >> col;

		vertexes.push_back({ type,{row,col} });
	}

	cin >> Q;

	for (int i{ 0 }; i < Q; ++i)
	{
		int src{ 0 }, dst{ 0 };
		cin >> src >> dst;

		query.push_back({ src,dst });
	}
}

void floydWarshall()
{
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
}

void solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		auto src{ vertexes[i] };
		auto type_src{ src.first };
		auto row_src{ src.second.first };
		auto col_src{ src.second.second };

		for (int j{ 0 }; j < N; ++j)
		{
			if (i == j)
			{
				dist[i + 1][j + 1] = 0;
				continue;
			}

			auto dst{ vertexes[j] };
			auto type_dst{ dst.first };
			auto row_dst{ dst.second.first };
			auto col_dst{ dst.second.second };

			auto w{ abs(row_src - row_dst) + abs(col_src - col_dst) };

			if (type_src == 1 && type_dst == 1)
			{
				if (T > w)
					dist[i + 1][j + 1] = w;
				else
					dist[i + 1][j + 1] = T;
			}
			else
			{
				auto w{ abs(row_src - row_dst) + abs(col_src - col_dst) };

				dist[i + 1][j + 1] = w;
			}
		}
	}

	floydWarshall();

	for (int i{ 0 }; i < Q; ++i)
	{
		auto src{ query[i].first };
		auto dst{ query[i].second };

		cout << dist[src][dst] << endl;
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