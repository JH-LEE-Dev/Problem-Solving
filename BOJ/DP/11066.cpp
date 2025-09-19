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
#define MAX 501

int T, N;
vector<vector<int>> DP;
vector<int> Arr;
vector<int> Sum;

void Input()
{
	Arr.clear();
	DP = vector<vector<int>>(MAX, vector<int>(MAX, INF));
	Sum = vector<int>(MAX, 0);

	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		int Temp;
		cin >> Temp;
		Arr.push_back(Temp);

		Sum[i] = Sum[i - 1] + Arr[i - 1];
		DP[i][i] = 0;
	}
}

void Solve()
{
	cin >> T;

	while (T != 0)
	{
		Input();

		// 구간 길이
		for (int len = 2; len <= N; len++)
		{
			for (int i = 1; i + len - 1 <= N; i++)
			{
				int j = i + len - 1;
				DP[i][j] = INF;

				for (int k = i; k < j; k++)
				{
					DP[i][j] = min(DP[i][j],
						DP[i][k] + DP[k + 1][j] + (Sum[j] - Sum[i - 1]));
				}
			}
		}

		cout << DP[1][N] << endl;

		--T;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}