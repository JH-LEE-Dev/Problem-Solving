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
#define INF numeric_limits<int>::max()
#define MAX 4'001

vector<vector<int>> dp(MAX, vector<int>(MAX, 0));
string a, b;
int maxVal{ 0 };

void Input()
{
	cin >> a >> b;
}

void Solve()
{
	for (int i{ 1 }; i <= a.length(); ++i)
	{
		for (int j{ 1 }; j <= b.length(); ++j)
		{
			if (a[i - 1] == b[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
				maxVal = max(maxVal, dp[i][j]);
			}
			else
			{
				dp[i][j] = 0;
			}
		}
	}

	cout << maxVal;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();

	return 0;
}