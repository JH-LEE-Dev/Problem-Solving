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
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 1'001
#define MOD 10'007

int N{ 0 }, M{ 0 };
vector<vector<int>> DP(MAX, vector<int>(MAX, 0));

void func(int n, int m)
{
	for (int i{ 0 }; i <= n; ++i)
	{
		DP[i][0] = 1;
	}

	for (int i{ 1 }; i <= n; ++i)
	{
		for (int j{ 1 }; j <= min(i, m); ++j)
		{
			DP[i][j] = (DP[i - 1][j] % MOD + DP[i - 1][j - 1] % MOD) % MOD;
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	func(N, M);
	cout << DP[N][M];

	return 0;
}