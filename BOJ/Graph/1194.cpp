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
using Vertex = tuple<int, int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 51

int N, M;
vector<vector<char>> Table(MAX, vector<char>(MAX, '.'));
vector<vector<vector<int>>> Dist(MAX, vector<vector<int>>(MAX, vector<int>(1 << 6, INF)));
map<char, char> DoorToKey;
pair<int, int> Start;

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0 || Table[R][C] == '#')
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

			if (Table[i][j] == '0')
			{
				Start.first = i;
				Start.second = j;
			}
		}
	}

	DoorToKey['A'] = 'a';
	DoorToKey['B'] = 'b';
	DoorToKey['C'] = 'c';
	DoorToKey['D'] = 'd';
	DoorToKey['E'] = 'e';
	DoorToKey['F'] = 'f';
}

void Bfs()
{
	queue<Vertex> Q;
	Q.push({ 0,Start.first,Start.second,0 });
	Dist[Start.first][Start.second][0] = 0;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<1>(Cur) };
		auto C{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurState{ get<3>(Cur) };

		if (Table[R][C] == '1')
		{
			cout << CurDist;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };
			auto NewState{ CurState };
			auto NewDist{ CurDist + 1 };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] >= (int)'a' && Table[NewR][NewC] <= (int)'f')
			{
				NewState = NewState | (1 << (Table[NewR][NewC] - 'a'));
			}

			if ((int)Table[NewR][NewC] >= (int)'A' && (int)Table[NewR][NewC] <= (int)'F')
			{
				char Key{ DoorToKey[Table[NewR][NewC]] };

				int DoorMatch{ NewState & (1 << (Key - 'a')) };

				if (DoorMatch != (1 << (Key - 'a')))
					continue;
			}

			if (Dist[NewR][NewC][NewState] == INF)
			{
				Dist[NewR][NewC][NewState] = NewDist;
				Q.push({ NewDist,NewR,NewC,NewState });
			}
		}
	}

	cout << -1;
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