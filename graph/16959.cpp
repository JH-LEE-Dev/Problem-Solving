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

#define MAX 301
#define endl '\n'
#define INF numeric_limits<int>::max()/2
#define NO_CHANGE 1000
#define CHANGE 1001
#define KNIGHT_RANGE 0
#define ROOK_RANGE 200
#define BISHOP_RANGE 100

vector<int> kn_dir_r{ 1, 2, 2, 1, -1, -2, -2, -1 };
vector<int> kn_dir_c{ 2, 1, -1, -2, -2, -1, 1, 2 };

int N{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<vector<int>> DP(MAX, vector<int>(MAX, INF));
vector<int> row(101, 0);
vector<int> col(101, 0);

int convert(int r, int c)
{
	return r * N + c;
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= N || c < 0)
		return false;
	else
		return true;
}

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			int num{ 0 };
			cin >> num;
			num;

			row[num] = i;
			col[num] = j;
		}
	}
}

void floydWarshall()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			dist[convert(i, j) + KNIGHT_RANGE][convert(i, j) + KNIGHT_RANGE] = 0;

			//KNIGHT
			for (int k{ 0 }; k < 8; ++k)
			{
				int r{ i + kn_dir_r[k] };
				int c{ j + kn_dir_c[k] };

				if (isValid(r, c))
				{
					dist[convert(i, j) + KNIGHT_RANGE][convert(r, c) + KNIGHT_RANGE] = NO_CHANGE;
				}
			}

			//BISHOP
			auto nR{ i };
			auto nC{ j };

			dist[convert(i, j) + BISHOP_RANGE][convert(i, j) + BISHOP_RANGE] = 0;

			while (true)
			{
				--nR;
				--nC;

				if (isValid(nR, nC) == false)
				{
					nR = i;
					nC = j;
					break;
				}

				dist[convert(i, j) + BISHOP_RANGE][convert(nR, nC) + BISHOP_RANGE] = NO_CHANGE;
			}

			while (true)
			{
				--nR;
				++nC;

				if (isValid(nR, nC) == false)
				{
					nR = i;
					nC = j;
					break;
				}

				dist[convert(i, j) + BISHOP_RANGE][convert(nR, nC) + BISHOP_RANGE] = NO_CHANGE;
			}

			while (true)
			{
				++nR;
				--nC;

				if (isValid(nR, nC) == false)
				{
					nR = i;
					nC = j;
					break;
				}

				dist[convert(i, j) + BISHOP_RANGE][convert(nR, nC) + BISHOP_RANGE] = NO_CHANGE;
			}

			while (true)
			{
				++nR;
				++nC;

				if (isValid(nR, nC) == false)
				{
					nR = i;
					nC = j;
					break;
				}

				dist[convert(i, j) + BISHOP_RANGE][convert(nR, nC) + BISHOP_RANGE] = NO_CHANGE;
			}

			//ROOK
			dist[convert(i, j) + ROOK_RANGE][convert(i, j) + ROOK_RANGE] = 0;

			while (true)
			{
				--nC;

				if (isValid(nR, nC) == false)
				{
					nR = i;
					nC = j;
					break;
				}

				dist[convert(i, j) + ROOK_RANGE][convert(nR, nC) + ROOK_RANGE] = NO_CHANGE;
			}

			while (true)
			{
				++nC;

				if (isValid(nR, nC) == false)
				{
					nR = i;
					nC = j;
					break;
				}

				dist[convert(i, j) + ROOK_RANGE][convert(nR, nC) + ROOK_RANGE] = NO_CHANGE;
			}

			while (true)
			{
				++nR;

				if (isValid(nR, nC) == false)
				{
					nR = i;
					nC = j;
					break;
				}

				dist[convert(i, j) + ROOK_RANGE][convert(nR, nC) + ROOK_RANGE] = NO_CHANGE;
			}

			while (true)
			{
				--nR;

				if (isValid(nR, nC) == false)
				{
					nR = i;
					nC = j;
					break;
				}

				dist[convert(i, j) + ROOK_RANGE][convert(nR, nC) + ROOK_RANGE] = NO_CHANGE;
			}


			//Change
			dist[convert(i, j) + KNIGHT_RANGE][convert(i, j) + BISHOP_RANGE] = CHANGE;
			dist[convert(i, j) + KNIGHT_RANGE][convert(i, j) + ROOK_RANGE] = CHANGE;
			dist[convert(i, j) + BISHOP_RANGE][convert(i, j) + KNIGHT_RANGE] = CHANGE;
			dist[convert(i, j) + BISHOP_RANGE][convert(i, j) + ROOK_RANGE] = CHANGE;
			dist[convert(i, j) + ROOK_RANGE][convert(i, j) + KNIGHT_RANGE] = CHANGE;
			dist[convert(i, j) + ROOK_RANGE][convert(i, j) + BISHOP_RANGE] = CHANGE;
		}
	}

	for (int middle{ 0 }; middle < MAX; ++middle)
	{
		for (int left{ 0 }; left < MAX; ++left)
		{
			for (int right{ 0 }; right < MAX; ++right)
			{
				dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
			}
		}
	}
}

void solve()
{
	floydWarshall();

	DP[1][0] = 0;
	DP[1][1] = 0;
	DP[1][2] = 0;

	for (int i{ 2 }; i <= N * N; ++i)
	{
		DP[i][0] = min(DP[i][0], dist[convert(row[i - 1], col[i - 1]) + KNIGHT_RANGE][convert(row[i], col[i]) + KNIGHT_RANGE] + DP[i - 1][0]);
		DP[i][1] = min(DP[i][1], dist[convert(row[i - 1], col[i - 1]) + KNIGHT_RANGE][convert(row[i], col[i]) + BISHOP_RANGE] + DP[i - 1][0]);
		DP[i][2] = min(DP[i][2], dist[convert(row[i - 1], col[i - 1]) + KNIGHT_RANGE][convert(row[i], col[i]) + ROOK_RANGE] + DP[i - 1][0]);
		DP[i][0] = min(DP[i][0], dist[convert(row[i - 1], col[i - 1]) + BISHOP_RANGE][convert(row[i], col[i]) + KNIGHT_RANGE] + DP[i - 1][1]);
		DP[i][1] = min(DP[i][1], dist[convert(row[i - 1], col[i - 1]) + BISHOP_RANGE][convert(row[i], col[i]) + BISHOP_RANGE] + DP[i - 1][1]);
		DP[i][2] = min(DP[i][2], dist[convert(row[i - 1], col[i - 1]) + BISHOP_RANGE][convert(row[i], col[i]) + ROOK_RANGE] + DP[i - 1][1]);
		DP[i][0] = min(DP[i][0], dist[convert(row[i - 1], col[i - 1]) + ROOK_RANGE][convert(row[i], col[i]) + KNIGHT_RANGE] + DP[i - 1][2]);
		DP[i][1] = min(DP[i][1], dist[convert(row[i - 1], col[i - 1]) + ROOK_RANGE][convert(row[i], col[i]) + BISHOP_RANGE] + DP[i - 1][2]);
		DP[i][2] = min(DP[i][2], dist[convert(row[i - 1], col[i - 1]) + ROOK_RANGE][convert(row[i], col[i]) + ROOK_RANGE] + DP[i - 1][2]);
	}

	auto result{ min(DP[N * N][0],min(DP[N * N][1],DP[N * N][2])) };

	cout << result / NO_CHANGE;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}