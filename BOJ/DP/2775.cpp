#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> DP(15, vector<int>(15, 0));

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T{ 0 };
	cin >> T;

	while (T != 0)
	{
		int k{ 0 }, n{ 0 }, result{ 0 };
		cin >> k >> n;

		for (int i = 0; i <= k; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				if (j == 1)
				{
					DP[i][j] = 1;
					continue;
				}

				if (i == 0)
				{
					DP[i][j] = j;
					continue;
				}

				DP[i][j] = DP[i - 1][j] + DP[i][j - 1];
			}
		}

		cout << DP[k][n] << '\n';

		--T;
	}

	return 0;
}
