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
#define MAX 9

vector<vector<int>> Table(10, vector<int>(10, 0));
int EmptyCnt;
vector<pair<int, int>> EmptySpaces;

void Input()
{
	for (int i{ 0 }; i < MAX; ++i)
	{
		for (int j{ 0 }; j < MAX; ++j)
		{
			cin >> Table[i][j];

			if (Table[i][j] == 0)
			{
				++EmptyCnt;
				EmptySpaces.push_back({ i,j });
			}
		}
	}
}

bool Check(int R, int C, int Num)
{
	for (int i{ 0 }; i < MAX; ++i)
	{
		if (i == C)
			continue;

		if (Table[R][i] == Num)
			return false;
	}

	for (int i{ 0 }; i < MAX; ++i)
	{
		if (i == R)
			continue;

		if (Table[i][C] == Num)
			return false;
	}

	int BoxR{ R / 3 * 3 };
	int BoxC{ C / 3 * 3 };

	for (int i{ BoxR }; i < BoxR + 3; ++i)
	{
		for (int j{ BoxC }; j < BoxC + 3; ++j)
		{
			if (Table[i][j] == Num)
				return false;
		}
	}

	return true;
}

bool Dfs(int Cnt, int Idx)
{
	if (Cnt == EmptyCnt)
	{
		for (int i{ 0 }; i < MAX; ++i)
		{
			for (int j{ 0 }; j < MAX; ++j)
			{
				cout << Table[i][j] << ' ';
			}

			cout << endl;
		}

		return true;
	}

	if (Idx >= EmptySpaces.size())
		return false;

	auto [i, j] {EmptySpaces[Idx]};

	if (Table[i][j] == 0)
	{
		for (int k{ 1 }; k < 10; ++k)
		{
			if (Check(i, j, k) == true)
			{
				Table[i][j] = k;

				if (Dfs(1 + Cnt, Idx + 1))
					return true;

				Table[i][j] = 0;
			}
		}
	}

	return false;
}

void Solve()
{
	Dfs(0, 0);
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