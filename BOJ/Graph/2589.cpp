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
#define MAX 51

int N, M;
vector<vector<char>> Table(MAX, vector<char>(MAX, 0));
vector<pair<int, int>> Lands;

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };
int Result{ 0 };

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

			if (Table[i][j] == 'L')
				Lands.push_back({ i,j });
		}
	}
}

void Bfs(pair<int, int> Start)
{
	vector<vector<int>> Dist(MAX, vector<int>(MAX, -1));
	queue<State> Q;
	Q.push({ 0,Start.first,Start.second });
	Dist[Start.first][Start.second] = 0;
	int Max{ 0 };

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto [CurDist, R, C] {Cur};

		Max = max(CurDist, Max);

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false || Table[NewR][NewC] == 'W')
				continue;

			if (Dist[NewR][NewC] == -1)
			{
				Dist[NewR][NewC] = CurDist + 1;
				Q.push({ CurDist + 1,NewR,NewC });
			}
		}
	}

	Result = max(Max, Result);
}

void Solve()
{
	for (const auto& P : Lands)
	{
		Bfs(P);
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