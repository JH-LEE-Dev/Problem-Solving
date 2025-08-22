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
using Vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'005

int T, N, M;
vector<vector<int>> Table;
vector<vector<int>> Dist;

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

int MaxFlower{ -1 };
int MaxDist{ -1 };

bool IsValid(int R, int C)
{
	if (R >= N + 2 || R < 0 || C >= M + 2 || C < 0)
		return false;
	else
		return true;
}

void Input()
{
	cin >> N >> M;

	MaxFlower = -1;
	MaxDist = -1;
	Table = vector<vector<int>>(MAX, vector<int>(MAX, -1));
	Dist = vector<vector<int>>(MAX, vector<int>(MAX, INF));

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= M; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

void Bfs()
{
	deque<Vertex> DQ;
	DQ.push_front({ 0,0,0 });
	Dist[0][0] = 0;

	while (DQ.empty() == false)
	{
		auto Cur{ DQ.front() };
		DQ.pop_front();

		auto R{ get<1>(Cur) };
		auto C{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[R][C] < CurDist)
			continue;

		if (Table[R][C] == 0)
			MaxDist = max(CurDist, MaxDist);

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };
			auto NewDist{ CurDist };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] == 1)
				++NewDist;

			if (Dist[NewR][NewC] > NewDist)
			{
				Dist[NewR][NewC] = NewDist;

				if (NewDist == CurDist)
					DQ.push_front({ NewDist,NewR,NewC });
				else
					DQ.push_back({ NewDist,NewR,NewC });
			}
		}
	}
}

void Solve()
{
	cin >> T;

	for (int i{ 0 }; i < T; ++i)
	{
		Input();
		Bfs();

		int Result{ 0 };

		for (int j{ 1 }; j <= N; ++j)
		{
			for (int k{ 1 }; k <= M; ++k)
			{
				if (Dist[j][k] == MaxDist && Table[j][k] == 0)
					++Result;
			}
		}

		cout << MaxDist << ' ' << Result << endl;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}