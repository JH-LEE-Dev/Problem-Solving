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
#define MAX 51

int N, M;
int W_Knight, W_Bishop, W_Rook;
vector<vector<int>> Table(MAX, vector<int>(MAX, -1));
pair<int, int> Start;
vector<vector<vector<vector<int>>>> Dist(MAX, vector<vector<vector<int>>>(MAX, vector<vector<int>>(3, vector<int>(1 << 4, INF))));

vector<int> Dir_Row_Knight{ -2,-2,-1,-1,1,1,2,2 };
vector<int> Dir_Col_Knight{ 1,-1,2,-2,2,-2,1,-1 };
vector<int> Dir_Row_Bishop{ 1,1,-1,-1 };
vector<int> Dir_Col_Bishop{ 1,-1,1,-1 };
vector<int> Dir_Row_Rook{ 0,0,-1,1 };
vector<int> Dir_Col_Rook{ 1,-1,0,0 };

void Input()
{
	cin >> N;
	cin >> W_Knight >> W_Bishop >> W_Rook;

	cin >> Start.first >> Start.second;
	cin >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int R, C;
		cin >> R >> C;

		Table[R][C] = i;
	}
}

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= N || C < 0)
		return false;
	else
		return true;
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,0,0,Start.first,Start.second });
	Dist[Start.first][Start.second][0][0] = 0;
	Dist[Start.first][Start.second][1][0] = 0;
	Dist[Start.first][Start.second][2][0] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto R{ get<3>(Cur) };
		auto C{ get<4>(Cur) };
		auto CurType{ get<2>(Cur) };
		auto CurState{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[R][C][CurType][CurState] < CurDist)
			continue;

		if (CurState == (1 << M) - 1)
		{
			cout << CurDist;
			return;
		}

		for (int i{ 0 }; i < 8; ++i)
		{
			auto NewR{ R + Dir_Row_Knight[i] };
			auto NewC{ C + Dir_Col_Knight[i] };
			auto NewDist{ CurDist + W_Knight };
			auto NewState{ CurState };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] != -1)
			{
				NewState |= (1 << Table[NewR][NewC]);
			}

			if (Dist[NewR][NewC][0][NewState] > NewDist)
			{
				Dist[NewR][NewC][0][NewState] = NewDist;
				PQ.push({ NewDist,NewState,0,NewR,NewC });
			}
		}

		//Bishop
		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row_Bishop[i] };
			auto NewC{ C + Dir_Col_Bishop[i] };

			while (true)
			{
				if (IsValid(NewR, NewC) == false)
					break;

				auto NewDist{ CurDist + W_Bishop };
				auto NewState{ CurState };

				if (Table[NewR][NewC] != -1)
				{
					NewState |= (1 << Table[NewR][NewC]);
				}

				if (Dist[NewR][NewC][1][NewState] > NewDist)
				{
					Dist[NewR][NewC][1][NewState] = NewDist;
					PQ.push({ NewDist,NewState,1,NewR,NewC });
				}

				NewR += Dir_Row_Bishop[i];
				NewC += Dir_Col_Bishop[i];
			}
		}

		//Rook
		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row_Rook[i] };
			auto NewC{ C + Dir_Col_Rook[i] };

			while (true)
			{
				if (IsValid(NewR, NewC) == false)
					break;

				auto NewDist{ CurDist + W_Rook };
				auto NewState{ CurState };

				if (Table[NewR][NewC] != -1)
				{
					NewState |= (1 << Table[NewR][NewC]);
				}

				if (Dist[NewR][NewC][2][NewState] > NewDist)
				{
					Dist[NewR][NewC][2][NewState] = NewDist;
					PQ.push({ NewDist,NewState,2,NewR,NewC });
				}

				NewR += Dir_Row_Rook[i];
				NewC += Dir_Col_Rook[i];
			}
		}
	}
}

void Solve()
{
	Dijkstra();
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