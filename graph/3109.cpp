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

int N, M;
vector<vector<bool>> Visited;
vector<vector<char>> Table;

vector<int> Dir_Row{ -1,0,1 };
vector<int> Dir_Col{ 1,1,1 };

int Result{ 0 };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0 || Table[R][C] == 'x')
		return false;
	else
		return true;
}

void Input()
{
	cin >> N >> M;

	Visited.resize(N, vector<bool>(M, false));
	Table.resize(N, vector<char>(M, '.'));

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

bool Dfs(pair<int, int> Start)
{
	auto R{ Start.first };
	auto C{ Start.second };

	Visited[R][C] = true;

	if (C == M - 1)
	{
		++Result;
		return true;
	}

	for (int i{ 0 }; i < 3; ++i)
	{
		auto NewR{ R + Dir_Row[i] };
		auto NewC{ C + Dir_Col[i] };

		if (IsValid(NewR, NewC) == false || Visited[NewR][NewC] == true)
			continue;

		if (Dfs({ NewR,NewC }))
			return true;
	}

	return false;
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		Dfs({ i,0 });
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