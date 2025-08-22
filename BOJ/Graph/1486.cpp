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

#define MAX 1001
#define endl '\n'
#define INF numeric_limits<int>::max()/2

int N{ 0 }, M{ 0 }, T{ 0 }, D{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, INF));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

vector<int> dir_row{ 0,0,-1,1 };
vector<int> dir_col{ 1,-1,0,0 };

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= M || col < 0)
		return false;
	else
		return true;
}

void input()
{
	cin >> N >> M >> T >> D;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			char h;
			cin >> h;

			if (h - 'a' < 0)
				table[i][j] = h - 'A';
			else
				table[i][j] = h - 'a' + 26;
		}
	}

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			auto coord_src{ M * i + j };

			for (int k{ 0 }; k < 4; ++k)
			{
				auto nR{ i + dir_row[k] };
				auto nC{ j + dir_col[k] };

				if (isValid(nR, nC))
				{
					auto coord_dst{ M * nR + nC };
					auto hDelta{ abs(table[i][j] - table[nR][nC]) };
					auto w{ 0 };

					if (hDelta > T)
						continue;

					if (table[i][j] < table[nR][nC])
						w = hDelta * hDelta;
					else
						w = 1;

					dist[coord_src][coord_dst] = w;
				}
			}
		}
	}
}

void floydWarshall()
{
	for (int i{ 0 }; i < N * M; ++i)
	{
		dist[i][i] = 0;
	}

	for (int middle{ 0 }; middle < N * M; ++middle)
	{
		for (int left{ 0 }; left < N * M; ++left)
		{
			for (int right{ 0 }; right < N * M; ++right)
			{
				dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
			}
		}
	}
}

void solve()
{
	floydWarshall();

	int result{ 0 };

	for (int i{ 0 }; i < N * M; ++i)
	{
		auto distSum{ dist[0][i] + dist[i][0] };

		if (distSum <= D)
		{
			auto row{ i / M };
			auto col{ i % M };

			result = max(result, table[row][col]);
		}
	}

	cout << result;
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