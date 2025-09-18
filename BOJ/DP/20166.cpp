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
#define MAX 11

int N, M, K;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<vector<int>>> Dist;
vector<string> Arr;

vector<int> Dir_Row{ 0,0,1,-1,1,-1,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0,1,-1,-1,1 };
vector<vector<pair<int, int>>> StartPoints(26, vector<pair<int, int>>());

void Input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		string Str;
		cin >> Str;

		for (int j{ 0 }; j < M; ++j)
		{
			Table[i][j] = Str[j];

			StartPoints[Table[i][j] - 'a'].push_back({ i,j });
		}
	}

	for (int i{ 0 }; i < K; ++i)
	{
		string Str;
		cin >> Str;

		Arr.push_back(Str);
	}
}

int Dfs(int R, int C, int Cnt, const string& Target)
{
	if (Dist[R][C][Cnt] != -1)
		return Dist[R][C][Cnt];

	if (Cnt == Target.length() - 1)
		return 1;

	Dist[R][C][Cnt] = 0;

	for (int i{ 0 }; i < 8; ++i)
	{
		auto NewR{ R + Dir_Row[i] };
		auto NewC{ C + Dir_Col[i] };
		auto NewCnt{ Cnt + 1 };

		if (NewR >= N)
			NewR = 0;

		if (NewR < 0)
			NewR = N - 1;

		if (NewC >= M)
			NewC = 0;

		if (NewC < 0)
			NewC = M - 1;

		if (Table[NewR][NewC] != Target[NewCnt])
			continue;

		Dist[R][C][Cnt] += Dfs(NewR, NewC, NewCnt, Target);
	}

	return Dist[R][C][Cnt];
}

void Solve()
{
	for (int i{ 0 }; i < K; ++i)
	{
		Dist = vector<vector<vector<int>>>(MAX, vector<vector<int>>(MAX, vector<int>(5, -1)));
		int Result{ 0 };

		for (const auto& P : StartPoints[Arr[i][0] - 'a'])
		{
			auto [R, C] {P};

			Result += Dfs(R, C, 0, Arr[i]);
		}

		cout << Result << endl;
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