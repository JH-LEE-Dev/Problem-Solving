#include <iostream>
#include <vector>
#include <limits>

#define endl '\n'
using namespace std;

vector<vector<int>> table(10, vector<int>(10, 0));
std::vector<std::vector<std::vector<int>>> DP(10, std::vector<std::vector<int>>(10, std::vector<int>(3, numeric_limits<int>::max())));

int N{ 0 }, M{ 0 }, result{ numeric_limits<int>::max() };

enum DIR { LEFT = -1, DOWN = 0, RIGHT = 1, DEFAULT = 3 };

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];
			DP[i][j][0] = table[i][j];
			DP[i][j][1] = table[i][j];
			DP[i][j][2] = table[i][j];

			if (j == 0)
			{
				DP[i][j][0] = numeric_limits<int>::max();
			}

			if (j == M - 1)
			{
				DP[i][j][2] = numeric_limits<int>::max();
			}
		}
	}

	for (int i{ 1 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (j != 0)
			{
				DP[i][j][0] += min(DP[i - 1][j - 1][1], DP[i - 1][j - 1][2]);
			}

			DP[i][j][1] += min(DP[i - 1][j][0], DP[i - 1][j][2]);

			if (j != M - 1)
			{
				DP[i][j][2] += min(DP[i - 1][j + 1][0], DP[i - 1][j + 1][1]);
			}
		}
	}

	for (int i{ 0 }; i < M; ++i)
	{
		for (int j{ 0 }; j < 3; ++j)
		{
			result = min(DP[N - 1][i][j], result);
		}
	}

	cout << result;

	return 0;
}