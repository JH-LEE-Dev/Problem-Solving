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
#define MAX 500'000

int A, B;
vector<vector<int>> Dist(MAX + 1, vector<int>(2, INF));
vector<int> TargetDist(MAX + 1, INF);

void Input()
{
	cin >> A >> B;

	int Time{ 0 };
	for (int i{ 0 }; B + Time <= MAX;)
	{
		TargetDist[B + Time] = i;
		++i;
		Time += i;
	}
}

int Bfs()
{
	int Result{ INF };

	queue<tuple<int, int>> Q;
	Q.push({ 0,A });

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		auto NewDist{ CurDist + 1 };
		auto NewRemain{ NewDist % 2 };

		if (TargetDist[Src] % 2 == CurDist % 2)
		{
			if (TargetDist[Src] >= CurDist)
				Result = min(TargetDist[Src], Result);
		}

		if (Src > 0)
		{
			auto LeftSide{ Src - 1 };

			if (Dist[LeftSide][NewRemain] == INF)
			{
				Dist[LeftSide][NewRemain] = NewDist;
				Q.push({ NewDist,LeftSide });
			}
		}

		if (Src < MAX)
		{
			auto RightSide{ Src + 1 };

			if (Dist[RightSide][NewRemain] == INF)
			{
				Dist[RightSide][NewRemain] = NewDist;
				Q.push({ NewDist,RightSide });
			}
		}

		if (Src * 2 <= MAX)
		{
			auto JumpPoint{ Src * 2 };

			if (Dist[JumpPoint][NewRemain] == INF)
			{
				Dist[JumpPoint][NewRemain] = NewDist;
				Q.push({ NewDist,JumpPoint });
			}
		}
	}

	if (Result == INF)
		return -1;
	else
		return Result;
}

void Solve()
{
	cout << Bfs();
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