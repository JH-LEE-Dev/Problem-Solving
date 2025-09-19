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
#define MAX 2'001

int N, M;
vector<int> Arr(MAX);
vector<vector<bool>> DP(MAX, vector<bool>(MAX, 0));
vector<pair<int, int>>Query;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> Arr[i];
	}

	cin >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int S, E;
		cin >> S >> E;

		Query.push_back({ S,E });
	}
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N - i; ++j)
		{
			if (i == 0)
			{
				DP[j][j] = 1;
				continue;
			}

			if (i == 1)
			{
				if (Arr[j] == Arr[j + i])
					DP[j][j + i] = true;
			}
			else
			{
				if (Arr[j] == Arr[j + i] && DP[j + 1][j + i - 1] == true)
					DP[j][j + i] = true;
			}
		}
	}

	for (const auto& P : Query)
	{
		auto [S, E] {P};

		cout << DP[S - 1][E - 1] << endl;
	}
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