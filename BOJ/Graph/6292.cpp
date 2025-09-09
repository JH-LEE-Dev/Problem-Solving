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
using State = tuple<char, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 4'001

int N, M;
vector<vector<char>> Table(MAX, vector<char>(MAX, '.'));
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));
vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };
int Result{ 0 };
queue<State> Q_One;
queue<State> Q_Two;

char OneChar;
char TwoChar;

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

void Bfs_One()
{
	while (Q_One.empty() == false)
	{
		auto Cur{ Q_One.front() };
		Q_One.pop();

		auto R{ get<1>(Cur) };
		auto C{ get<2>(Cur) };
		auto CurType{ get<0>(Cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false || Table[NewR][NewC] == '.')
				continue;

			if (Visited[NewR][NewC] == false)
			{
				Visited[NewR][NewC] = true;

				if (Table[NewR][NewC] != CurType)
				{
					Q_Two.push({ Table[NewR][NewC],NewR,NewC });
				}
				else
				{
					Q_One.push({ CurType,NewR,NewC });
				}
			}
		}
	}
}

void Bfs_Two()
{
	while (Q_Two.empty() == false)
	{
		auto Cur{ Q_Two.front() };
		Q_Two.pop();

		auto R{ get<1>(Cur) };
		auto C{ get<2>(Cur) };
		auto CurType{ get<0>(Cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false || Table[NewR][NewC] == '.')
				continue;

			if (Visited[NewR][NewC] == false)
			{
				Visited[NewR][NewC] = true;

				if (Table[NewR][NewC] != CurType)
				{
					Q_One.push({ Table[NewR][NewC],NewR,NewC });
				}
				else
				{
					Q_Two.push({ CurType,NewR,NewC });
				}
			}
		}
	}
}

void Solve()
{
	OneChar = Table[0][0];

	if (OneChar == 'F')
		TwoChar = 'R';
	else
		TwoChar = 'F';

	Q_One.push({ Table[0][0],0,0 });
	Visited[0][0] = true;

	while (true)
	{
		if (Q_One.empty())
			break;

		++Result;

		Bfs_One();

		if (Q_Two.empty())
			break;

		++Result;

		Bfs_Two();
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