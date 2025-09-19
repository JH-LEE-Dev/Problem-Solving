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

int N;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<vector<int>>> DP(MAX, vector<vector<int>>(MAX, vector<int>(5, -1)));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= N || C < 0)
		return false;
	else
		return true;
}

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

int Dfs(int R, int C, int Type)
{
	if (DP[R][C][Type] != -1)
		return DP[R][C][Type];

	DP[R][C][Type] = 1;

	for (int i{ 0 }; i < 4; ++i)
	{
		auto NewR{ R + Dir_Row[i] };
		auto NewC{ C + Dir_Col[i] };

		if (IsValid(NewR, NewC) == false)
			continue;

		if (Table[R][C] >= Table[NewR][NewC])
			continue;

		DP[R][C][Type] = max(Dfs(NewR, NewC, i) + 1, DP[R][C][Type]);
	}

	return DP[R][C][Type];
}

void Solve()
{
	int Result{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			Result = max(Result, Dfs(i, j, 4));
		}
	}

	cout << Result;
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