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
#define MAX 101

int N, K, M;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));
set<pair<int, int>> Roads;
set<pair<int, int>> Cows;

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

int Result;

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= N || C < 0)
		return false;
	else
		return true;
}

int GetID(int R, int C)
{
	return R * N + C;
}

void Input()
{
	cin >> N >> K >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int R1, C1, R2, C2;
		cin >> R1 >> C1 >> R2 >> C2;

		int Src{ GetID(R1 - 1,C1 - 1) };
		int Dst{ GetID(R2 - 1,C2 - 1) };

		if (Src > Dst)
			swap(Src, Dst);

		Roads.insert({ Src,Dst });
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int R, C;
		cin >> R >> C;

		Cows.insert({ R - 1,C - 1 });
	}

	Result = K * (K - 1) / 2;
}

void Bfs(pair<int, int> Start)
{
	queue<pair<int, int>> Q;
	Q.push({ Start.first,Start.second });
	Visited[Start.first][Start.second] = true;

	int Cnt{ 1 };

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto [R, C] {Cur};
		auto ID{ GetID(R,C) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			auto SrcID{ ID };
			auto DstID{ GetID(NewR,NewC) };

			if (SrcID > DstID)
				swap(SrcID, DstID);

			if (Roads.find({ SrcID,DstID }) == Roads.end())
			{
				if (Visited[NewR][NewC] == false)
				{
					Visited[NewR][NewC] = true;
					Q.push({ NewR,NewC });

					if (Cows.find({ NewR,NewC }) != Cows.end())
						++Cnt;
				}
			}
		}
	}

	Result -= Cnt * (Cnt - 1) / 2;
}

void Solve()
{
	for (const auto& Cow : Cows)
	{
		auto [R, C] {Cow};

		if (Visited[R][C] == false)
			Bfs(Cow);
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