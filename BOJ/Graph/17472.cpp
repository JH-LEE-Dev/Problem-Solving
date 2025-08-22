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

int N, M;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<int>> Group(MAX, vector<int>(MAX, -1));
vector<vector<int>> Dist(7, vector<int>(7, INF));
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));
vector<vector<bool>> Bridge(7, vector<bool>(7, false));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

int Cnt{ 0 };
int Result{ INF };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0)
		return false;
	else
		return true;
}

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

void Bfs(pair<int, int> Start, int Idx)
{
	queue<pair<int, int>> Q;
	Q.push({ Start.first,Start.second });
	Visited[Start.first][Start.second] = true;
	Group[Start.first][Start.second] = Idx;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<0>(Cur) };
		auto C{ get<1>(Cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Visited[NewR][NewC] == false && Table[NewR][NewC] == 1)
			{
				Visited[NewR][NewC] = true;
				Q.push({ NewR,NewC });
				Group[NewR][NewC] = Idx;
			}
		}
	}
}

void DistBfs(int Idx)
{
	queue<tuple<int, int, int, int>> Q;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (Group[i][j] == Idx)
			{
				Q.push({ 0, -1,i,j });
			}
		}
	}

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<2>(Cur) };
		auto C{ get<3>(Cur) };
		auto CurDir{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (CurDir == -1)
		{
			for (int i{ 0 }; i < 4; ++i)
			{
				auto NewR{ R + Dir_Row[i] };
				auto NewC{ C + Dir_Col[i] };
				auto NewDist{ CurDist + 1 };

				if (IsValid(NewR, NewC) == false)
					continue;

				if (Table[NewR][NewC] != 1)
				{
					Q.push({ NewDist,i,NewR,NewC });
				}
			}
		}
		else
		{
			auto NewR{ R + Dir_Row[CurDir] };
			auto NewC{ C + Dir_Col[CurDir] };
			auto NewDist{ CurDist + 1 };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] == 1)
			{
				if (NewDist == 2)
					continue;

				Dist[Idx][Group[NewR][NewC]] = min(Dist[Idx][Group[NewR][NewC]], NewDist - 1);
				Dist[Group[NewR][NewC]][Idx] = min(Dist[Group[NewR][NewC]][Idx], NewDist - 1);
			}
			else
			{
				Q.push({ NewDist,CurDir,NewR,NewC });
			}
		}
	}
}

bool IsLinkedBfs()
{
	int VisitCnt{ 1 };

	vector<bool> Visited(Cnt, false);
	queue<int> Q;
	Q.push(0);
	Visited[0] = true;

	while (Q.empty() == false)
	{
		auto Src{ Q.front() };
		Q.pop();

		for (int i{ 0 }; i < Cnt; ++i)
		{
			if (Src == i)
				continue;

			if (Visited[i] == false && (Bridge[Src][i] == true || Bridge[i][Src] == true))
			{
				Q.push(i);
				Visited[i] = true;
				++VisitCnt;
			}
		}
	}

	if (VisitCnt == Cnt)
		return true;
	else
		return false;
}

void Dfs(int Total, int LinkCount)
{
	if (LinkCount == Cnt - 1)
	{
		if (IsLinkedBfs())
			Result = min(Result, Total);

		return;
	}

	for (int i{ 0 }; i < Cnt; ++i)
	{
		for (int j{ i }; j < Cnt; ++j)
		{
			if (i == j || Dist[i][j] == INF || Dist[j][i] == INF)
				continue;

			if (Bridge[i][j] == true || Bridge[j][i] == true)
				continue;

			Bridge[i][j] = true;
			Bridge[j][i] = true;

			Dfs(Total + Dist[i][j], LinkCount + 1);

			Bridge[i][j] = false;
			Bridge[j][i] = false;
		}
	}
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (Visited[i][j] == false && Table[i][j] == 1)
			{
				Bfs({ i,j }, Cnt);
				++Cnt;
			}
		}
	}

	for (int i{ 0 }; i < Cnt; ++i)
	{
		DistBfs(i);
	}

	Dfs(0, 0);

	if (Result == INF)
		cout << -1;
	else
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