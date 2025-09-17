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
#define MAX 17

int N;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<vector<int>>> Dist(MAX, vector<vector<int>>(MAX, vector<int>(3, -1)));

vector<int> Dir_Row{ 0,1,1 };
vector<int> Dir_Col{ 1,1,0 };

bool IsValid(pair<int, int> Coord, int Type)
{
	auto [R, C] {Coord};

	if (R >= N || R < 0 || C >= N || C < 0 || Table[R][C] == 1)
		return false;

	switch (Type)
	{
	case 0:
	{
		auto NewR{ R + Dir_Row[0] };
		auto NewC{ C + Dir_Col[0] };

		if (NewR >= N || NewR < 0 || NewC >= N || NewC < 0 || Table[NewR][NewC] == 1)
			return false;
		else
			return true;

		break;
	}
	case 1:
	{
		for (int i{ 0 }; i < 3; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (NewR >= N || NewR < 0 || NewC >= N || NewC < 0 || Table[NewR][NewC] == 1)
				return false;
		}

		return true;

		break;
	}
	case 2:
	{
		auto NewR{ R + Dir_Row[2] };
		auto NewC{ C + Dir_Col[2] };

		if (NewR >= N || NewR < 0 || NewC >= N || NewC < 0 || Table[NewR][NewC] == 1)
			return false;
		else
			return true;

		break;
	}
	}
}

bool Check(int R, int C, int Type)
{
	switch (Type)
	{
	case 0:
	{
		auto NewR{ R + Dir_Row[0] };
		auto NewC{ C + Dir_Col[0] };

		if (NewR >= N || NewR < 0 || NewC >= N || NewC < 0 || Table[NewR][NewC] == 1)
			return false;

		if (NewR == N - 1 && NewC == N - 1)
			return true;
		else
			return false;

		break;
	}
	case 1:
	{
		auto NewR{ R + Dir_Row[1] };
		auto NewC{ C + Dir_Col[1] };

		if (NewR >= N || NewR < 0 || NewC >= N || NewC < 0 || Table[NewR][NewC] == 1)
			return false;

		if (NewR == N - 1 && NewC == N - 1)
			return true;
		else
			return false;


		break;
	}
	case 2:
	{
		auto NewR{ R + Dir_Row[2] };
		auto NewC{ C + Dir_Col[2] };

		if (NewR >= N || NewR < 0 || NewC >= N || NewC < 0 || Table[NewR][NewC] == 1)
			return false;

		if (NewR == N - 1 && NewC == N - 1)
			return true;
		else
			return false;

		break;
	}
	}
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
	if (Dist[R][C][Type] != -1)
		return Dist[R][C][Type];

	if (Check(R, C, Type))
		return 1;

	Dist[R][C][Type] = 0;

	if (Type == 0)
	{
		auto NewR{ R + Dir_Row[0] };
		auto NewC{ C + Dir_Col[0] };

		for (int i{ 0 }; i < 2; ++i)
		{
			if (IsValid({ NewR,NewC }, i) == false)
				continue;

			Dist[R][C][Type] += Dfs(NewR, NewC, i);
		}
	}

	if (Type == 1)
	{
		auto NewR{ R + Dir_Row[1] };
		auto NewC{ C + Dir_Col[1] };

		for (int i{ 0 }; i < 3; ++i)
		{
			if (IsValid({ NewR,NewC }, i) == false)
				continue;

			Dist[R][C][Type] += Dfs(NewR, NewC, i);
		}
	}

	if (Type == 2)
	{
		auto NewR{ R + Dir_Row[2] };
		auto NewC{ C + Dir_Col[2] };

		for (int i{ 1 }; i < 3; ++i)
		{
			if (IsValid({ NewR,NewC }, i) == false)
				continue;

			Dist[R][C][Type] += Dfs(NewR, NewC, i);
		}
	}

	return Dist[R][C][Type];
}

void Solve()
{
	int Result{ 0 };

	Result += Dfs(0, 0, 0);

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