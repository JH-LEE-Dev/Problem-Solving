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
#define MAX 51

int N, M;
vector<vector<char>> Table(MAX, vector<char>(MAX, '.'));
vector<vector<pair<int, int>>> Island_Coord(16, vector<pair<int, int>>());
vector<vector<int>> Island(MAX, vector<int>(MAX, -1));
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));
vector<vector<int>> Dist_Island(16, vector<int>(16, INF));
vector<vector<int>> Dist_Result(16, vector<int>(1 << 16, -1));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

int Cnt;

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0 || Table[R][C] == '.')
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

void Bfs(pair<int, int> Start, int Cnt)
{
	queue<pair<int, int>> Q;
	Q.push({ Start.first,Start.second });
	Visited[Start.first][Start.second] = true;
	Island[Start.first][Start.second] = Cnt;
	Island_Coord[Cnt].push_back(Start);

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ Cur.first };
		auto C{ Cur.second };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Visited[NewR][NewC] == false && Table[NewR][NewC] == 'X')
			{
				Visited[NewR][NewC] = true;
				Q.push({ NewR,NewC });
				Island[NewR][NewC] = Cnt;
				Island_Coord[Cnt].push_back({ NewR,NewC });
			}
		}
	}
}

void Bfs_Dist(int Cnt)
{
	vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));

	deque<tuple<int, int, int>> DQ;

	for (int i{ 0 }; i < Island_Coord[Cnt].size(); ++i)
	{
		auto Coord{ Island_Coord[Cnt][i] };

		DQ.push_front({ 0,Coord.first,Coord.second });
		Dist[Coord.first][Coord.second] = 0;
	}

	while (DQ.empty() == false)
	{
		auto Cur{ DQ.front() };
		DQ.pop_front();

		auto R{ get<1>(Cur) };
		auto C{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };
			auto NewDist{ CurDist };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] == 'X')
			{
				if (Dist[NewR][NewC] > NewDist)
				{
					Dist[NewR][NewC] = NewDist;
					DQ.push_front({ NewDist,NewR,NewC });

					if (Table[NewR][NewC] == 'X' && Island[NewR][NewC] != Cnt)
					{
						Dist_Island[Cnt][Island[NewR][NewC]] = min(NewDist, Dist_Island[Cnt][Island[NewR][NewC]]);
					}
				}
			}
			else
			{
				NewDist += 1;

				if (Dist[NewR][NewC] > NewDist)
				{
					Dist[NewR][NewC] = NewDist;
					DQ.push_front({ NewDist,NewR,NewC });
				}
			}
		}
	}
}

int Dfs(int V, int CurBit)
{
	if (CurBit == (1 << Cnt) - 1)
		return 0;

	if (Dist_Result[V][CurBit] != -1)
		return Dist_Result[V][CurBit];

	Dist_Result[V][CurBit] = INF;

	for (int i{ 0 }; i < Cnt; ++i)
	{
		if ((CurBit & (1 << i)) == (1 << i))
			continue;

		int NewBit{ CurBit | (1 << i) };

		Dist_Result[V][CurBit] = min(Dist_Result[V][CurBit], Dfs(i, NewBit) + Dist_Island[V][i]);
	}

	return Dist_Result[V][CurBit];
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (Table[i][j] == 'X' && Visited[i][j] == false)
			{
				Bfs({ i,j }, Cnt);
				++Cnt;
			}
		}
	}

	for (int i{ 0 }; i < Cnt; ++i)
	{
		Bfs_Dist(i);
	}

	int Result{ INF };

	for (int i{ 0 }; i < Cnt; ++i)
	{
		Result = min(Result, Dfs(i, (1 << i)));
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