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
using State = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 501

int N, M;
int A, B, Limit;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));

pair<int, int> Start;
pair<int, int> End;

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

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

	cin >> Start.first >> Start.second;

	cin >> A >> B >> Limit;

	int Max{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];

			if (Max < Table[i][j])
			{
				Max = Table[i][j];
				End = { i,j };
			}
		}
	}
}

void Dijkstra()
{
	Start.first -= 1;
	Start.second -= 1;

	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ 0,Start.first,Start.second });
	Dist[Start.first][Start.second] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto [CurDist, R, C] {Cur};
		auto CurH{ Table[R][C] };

		if (Dist[R][C] < CurDist)
			continue;

		if (make_pair(R, C) == End)
		{
			cout << CurDist;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			auto NewH{ Table[NewR][NewC] };
			auto DeltaH{ CurH - NewH };

			if (abs(DeltaH) > Limit)
				continue;

			auto NewDist{ CurDist };

			if (DeltaH == 0)
				NewDist += 1;

			if (DeltaH > 0)
				NewDist += B * DeltaH;

			if (DeltaH < 0)
				NewDist += A * abs(DeltaH);

			if (Dist[NewR][NewC] > NewDist)
			{
				Dist[NewR][NewC] = NewDist;
				PQ.push({ NewDist,NewR,NewC });
			}
		}
	}

	cout << -1;
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