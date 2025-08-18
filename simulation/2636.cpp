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
#define MAX 105

int N, M;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
queue<pair<int, int>> MeltingQ;
queue<pair<int, int>> CheckQ;
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));
vector<vector<bool>> Melted(MAX, vector<bool>(MAX, false));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };
int PrevCnt{ 0 };
int Cnt{ 0 };

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

			if (Table[i][j] == 1)
			{
				++Cnt;
				++PrevCnt;
			}
		}
	}

	CheckQ.push({ 0,0 });
	Visited[0][0] = true;
}

void CheckBfs()
{
	while (CheckQ.empty() == false)
	{
		auto Cur{ CheckQ.front() };
		CheckQ.pop();

		auto R{ Cur.first };
		auto C{ Cur.second };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] == 1)
			{
				if (Melted[NewR][NewC] == false)
				{
					MeltingQ.push({ NewR,NewC });
					Melted[NewR][NewC] = true;
				}
			}
			else
			{
				if (Visited[NewR][NewC] == false)
				{
					Visited[NewR][NewC] = true;
					CheckQ.push({ NewR,NewC });
				}
			}
		}
	}
}

void Melting()
{
	while (MeltingQ.empty() == false)
	{
		auto Cur{ MeltingQ.front() };
		MeltingQ.pop();

		auto R{ Cur.first };
		auto C{ Cur.second };

		Table[R][C] = 0;

		CheckQ.push({ R,C });
	}
}

void Solve()
{
	int Time{ 0 };

	while (true)
	{
		PrevCnt = Cnt;

		CheckBfs();

		Cnt -= MeltingQ.size();

		Melting();

		++Time;

		if (Cnt == 0)
			break;
	}

	cout << Time << endl << PrevCnt;
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