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
using Vertex = tuple<int, int, int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 201

int N, M, K;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<pair<int, int>> Patterns;
vector<vector<vector<vector<int>>>> Dist(MAX, vector<vector<vector<int>>>(MAX, vector<vector<int>>(31, vector<int>(2, INF))));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0 || Table[R][C] == 1)
		return false;
	else
		return true;
}

void Input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];
		}
	}

	for (int i{ 0 }; i < 5; ++i)
	{
		for (int j{ 0 }; j < 5; ++j)
		{
			int Temp;
			cin >> Temp;

			if (Temp == 1)
			{
				Patterns.push_back({ i - 2,j - 2 });
			}
		}
	}
}

void Bfs()
{
	queue<Vertex> Q;
	Q.push({ 0,0,0,0,0 });
	Dist[0][0][0][0] = 0;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<3>(Cur) };
		auto C{ get<4>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurCnt{ get<1>(Cur) };
		auto CurType{ get<2>(Cur) };

		if (R == N - 1 && C == M - 1 && CurType == true)
		{
			cout << CurDist;
			return;
		}

		if (CurCnt < K)
		{
			for (int i{ 0 }; i < Patterns.size(); ++i)
			{
				auto NewR{ R + Patterns[i].first };
				auto NewC{ C + Patterns[i].second };
				auto NewType{ CurType };
				auto NewCnt{ CurCnt + 1 };
				auto NewDist{ CurDist + 1 };

				if (IsValid(NewR, NewC) == false)
					continue;

				if (Table[NewR][NewC] == 2)
					NewType = true;

				if (Dist[NewR][NewC][NewCnt][NewType] > NewDist)
				{
					Dist[NewR][NewC][NewCnt][NewType] = NewDist;
					Q.push({ NewDist,NewCnt,NewType,NewR,NewC });
				}
			}
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };
			auto NewType{ CurType };
			auto NewDist{ CurDist + 1 };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] == 2)
				NewType = true;

			if (Dist[NewR][NewC][CurCnt][NewType] > NewDist)
			{
				Dist[NewR][NewC][CurCnt][NewType] = NewDist;
				Q.push({ NewDist,CurCnt,NewType,NewR,NewC });
			}
		}
	}

	cout << -1;
}

void Solve()
{
	Bfs();
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