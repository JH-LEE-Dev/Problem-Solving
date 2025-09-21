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
using LL = long long;
using State = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 501


int N, M;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
pair<int, int> Start;

vector<int> Dir_Row{ 0,0,1,-1,1,1,-1,-1 };
vector<int> Dir_Col{ 1,-1,0,0,1,-1,1,-1 };

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

	cin >> Start.first >> Start.second;
	Start.first -= 1;
	Start.second -= 1;
}

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0)
		return false;
	else
		return true;
}

void Bfs()
{
	priority_queue < State, vector<State>, greater<State>> PQ;
	vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));
	Dist[Start.first][Start.second] = Table[Start.first][Start.second];

	LL Result{ 0 };
	int Height{ Table[Start.first][Start.second] };

	PQ.push({ Height,Start.first,Start.second });

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto [PrevH, R, C] {Cur};
		auto CurH{ Dist[R][C] };

		Result += 0 - max(Dist[R][C], Height);

		for (int i{ 0 }; i < 8; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] >= 0)
				continue;

			auto NewDist{ max(CurH,Dist[NewR][NewC]) };

			if (NewDist == INF)
				NewDist = max(CurH, Table[NewR][NewC]);

			if (Dist[NewR][NewC] > NewDist)
			{
				Dist[NewR][NewC] = NewDist;
				PQ.push({ Dist[NewR][NewC],NewR,NewC });
			}
		}
	}

	cout << Result;
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