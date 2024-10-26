#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

vector<vector<int>> DP(10'005, vector<int>(4, 0));

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	DP[1][1] = 1;

	DP[2][1] = 1;
	DP[2][2] = 1;

	DP[3][1] = 1;
	DP[3][2] = 1;
	DP[3][3] = 1;

	int T{ 0 }, N{ 0 };
	cin >> T;

	for (int i = 4; i <= 10'000; i++)
	{
		DP[i][1] = 1;
		DP[i][2] = DP[i - 2][1] + DP[i - 2][2];
		DP[i][3] = DP[i - 3][1] + DP[i - 3][2] + DP[i - 3][3];
	}

	while (T != 0)
	{
		cin >> N;

		cout << DP[N][1] + DP[N][2] + DP[N][3] << endl;
		--T;
	}

	return 0;
}