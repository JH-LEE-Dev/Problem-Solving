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
vector<vector<int>> Table(MAX, vector<int>(MAX, -1));
vector<vector<int>> RoomIdx(MAX, vector<int>(MAX, -1));
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));
vector<int> Cnt(MAX* MAX, 0);

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };
vector<int> WallBit{ 4,1,8,2 };

int Result{ 0 };
int MaxCnt{ 0 };

void Input()
{
	cin >> N >> M;
	swap(N, M);

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0)
		return false;
	else
		return true;
}

void Bfs(int Idx, int R, int C)
{
	queue<pair<int, int>> Q;
	Q.push({ R,C });
	Visited[R][C] = true;
	RoomIdx[R][C] = Idx;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto [R, C] {Cur};

		++Cnt[Idx];
		RoomIdx[R][C] = Idx;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if ((Table[R][C] & WallBit[i]) != 0)
				continue;

			if (Visited[NewR][NewC] == false)
			{
				Visited[NewR][NewC] = true;
				Q.push({ NewR,NewC });
			}
		}
	}

	MaxCnt = max(MaxCnt, Cnt[Idx]);
}

void Bfs_WallBreak(int R, int C)
{
	vector<vector<bool>> Visited_WallBreak(MAX, vector<bool>(MAX, false));
	queue<tuple<bool, int, int>>Q;
	Q.push({ false,R,C });

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto [bWallBreak, R, C] {Cur};
		auto CurRoomIdx{ RoomIdx[R][C] };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			bool bWall{ (Table[R][C] & WallBit[i]) != 0 };
			int NxtRoomIdx{ RoomIdx[NewR][NewC] };

			if (bWallBreak && bWall)
				continue;

			bWall = bWall || bWallBreak;

			if (bWall)
			{
				if (Visited_WallBreak[NewR][NewC] == false)
				{
					if (CurRoomIdx != NxtRoomIdx)
					{
						Result = max(Result, Cnt[CurRoomIdx] + Cnt[NxtRoomIdx]);
						continue;
					}

					Visited_WallBreak[NewR][NewC] = true;
					Q.push({ bWall,NewR,NewC });
				}
			}
			else
			{
				if (Visited[NewR][NewC] == false)
				{
					Visited[NewR][NewC] = true;
					Q.push({ bWall,NewR,NewC });
				}
			}
		}
	}
}

void Solve()
{
	int Idx{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (Visited[i][j] == false)
			{
				Bfs(Idx, i, j);
				++Idx;
			}
		}
	}

	Visited = vector<vector<bool>>(MAX, vector<bool>(MAX, false));

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (Visited[i][j] == false)
			{
				Bfs_WallBreak(i, j);
			}
		}
	}

	cout << Idx << endl;
	cout << MaxCnt << endl;
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