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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;
#define MAX 31

int W{ 0 }, H{ 0 }, G{ 0 }, E{ 0 };
vector<tuple<pair<int, int>, pair<int, int>, int>> edges;
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<vector<bool>> grave(MAX, vector<bool>(MAX, false));
vector<vector<bool>> warm(MAX, vector<bool>(MAX, false));
int numVertex{ 0 };

vector<int> dir_x{ 0,0,1,-1 };
vector<int> dir_y{ 1,-1,0,0 };

bool isValid(int row, int col)
{
	if (row >= W || row < 0 || col < 0 || col >= H)
		return false;
	else
		return true;
}

void generateGraph()
{
	for (int i{ 0 }; i < W; ++i)
	{
		for (int j{ 0 }; j < H; ++j)
		{
			if (i == W - 1 && j == H - 1)
				continue;

			if (warm[i][j] == true)
			{
				continue;
			}

			if (grave[i][j] == true)
				continue;

			for (int k{ 0 }; k < 4; ++k)
			{
				int row = i + dir_x[k];
				int col = j + dir_y[k];

				if (isValid(row, col) == false)
					continue;

				if (grave[row][col] == true)
					continue;

				edges.push_back({ {i,j},{row,col} ,1 });
			}
		}
	}
}

void bellmanford()
{
	dist[0][0] = 0;

	for (int i{ 0 }; i < numVertex - 1; ++i)
	{
		for (auto& edge : edges)
		{
			auto src{ get<0>(edge) };
			auto dst{ get<1>(edge) };
			auto w{ get<2>(edge) };

			auto row_src{ src.first };
			auto col_src{ src.second };

			auto row_dst{ dst.first };
			auto col_dst{ dst.second };

			if (dist[row_src][col_src] == INF)
				continue;

			if (dist[row_dst][col_dst] > dist[row_src][col_src] + w)
			{
				dist[row_dst][col_dst] = dist[row_src][col_src] + w;
			}
		}
	}

	bool cycled{ false };

	for (auto& edge : edges)
	{
		auto src{ get<0>(edge) };
		auto dst{ get<1>(edge) };
		auto w{ get<2>(edge) };

		auto row_src{ src.first };
		auto col_src{ src.second };

		auto row_dst{ dst.first };
		auto col_dst{ dst.second };

		if (dist[row_src][col_src] == INF)
			continue;

		if (dist[row_dst][col_dst] > dist[row_src][col_src] + w)
		{
			cycled = true;
			break;
		}
	}

	if (cycled)
	{
		cout << "Never" << endl;
	}
	else if (dist[W - 1][H - 1] == INF)
		cout << "Impossible" << endl;
	else
		cout << dist[W - 1][H - 1] << endl;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	while (true)
	{
		edges.clear();
		dist = vector<vector<int>>(MAX, vector<int>(MAX, INF));
		grave = vector<vector<bool>>(MAX, vector<bool>(MAX, false));
		warm = vector<vector<bool>>(MAX, vector<bool>(MAX, false));

		cin >> W >> H;

		if (W == 0 && H == 0)
			break;

		numVertex = W * H;

		cin >> G;

		for (int i{ 0 }; i < G; ++i)
		{
			int row{ 0 }, col{ 0 };

			cin >> row >> col;

			grave[row][col] = true;
		}

		cin >> E;

		for (int i{ 0 }; i < E; ++i)
		{
			int row_src{ 0 }, col_src{ 0 };
			int row_dst{ 0 }, col_dst{ 0 };
			int w{ 0 };

			cin >> row_src >> col_src >> row_dst >> col_dst >> w;

			edges.push_back({ {row_src,col_src},{row_dst,col_dst },w });

			warm[row_src][col_src] = true;
		}

		generateGraph();

		bellmanford();
	}

	return 0;
}