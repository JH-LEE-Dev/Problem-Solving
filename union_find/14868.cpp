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
#define MAX 2'001

int N, M;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
queue<pair<int, int>> Starts;
queue<pair<int, int>> InitialStarts;
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));
vector<int> Parents(MAX* MAX, -1);
vector<int> Rank(MAX* MAX, 1);

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };
vector<int> Count(MAX* MAX, 1);
int Unions;
bool bEnd{ false };

void Input()
{
	cin >> N >> M;

	int Cnt{ 0 };

	for (int i{ 0 }; i < MAX * MAX; ++i)
	{
		Parents[i] = i;
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int R, C;

		cin >> R >> C;

		Starts.push({ R - 1,C - 1 });
		InitialStarts.push({ R - 1,C - 1 });

		Table[R - 1][C - 1] = 1;
	}

	Unions = M;
}

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= N || C < 0)
		return false;
	else
		return true;
}

int Find(int U)
{
	if (Parents[U] == U)
		return U;

	return Parents[U] = Find(Parents[U]);
}

void Union(int U, int V)
{
	int Par_U{ Find(U) };
	int Par_V{ Find(V) };

	if (Par_U == Par_V)
		return;

	if (Rank[Par_U] > Rank[Par_V])
		swap(Par_U, Par_V);

	Parents[Par_U] = Par_V;
	Count[Par_V] += Count[Par_U];

	if (Count[Par_V] == Unions)
		bEnd = true;

	if (Rank[Par_U] == Rank[Par_V])
		++Rank[Par_V];
}

void InitialBfs()
{
	queue<tuple<int, int>> Q;

	while (InitialStarts.empty() == false)
	{
		auto Cur{ InitialStarts.front() };

		Q.push({ Cur.first,Cur.second });
		InitialStarts.pop();
	}

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<0>(Cur) };
		auto C{ get<1>(Cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] == 1)
				Union(R * N + C, NewR * N + NewC);
		}
	}
}

void Bfs()
{
	queue<tuple<int, int, bool>> Q;

	while (Starts.empty() == false)
	{
		auto Cur{ Starts.front() };

		Q.push({ Cur.first,Cur.second,false });
		Starts.pop();

		Visited[Cur.first][Cur.second] = true;
	}

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<0>(Cur) };
		auto C{ get<1>(Cur) };
		auto bNewUnios{ get<2>(Cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (bNewUnios == false)
			{
				Visited[NewR][NewC] = true;

				if (Table[NewR][NewC] == 0)
				{
					Starts.push({ NewR,NewC });
					++Unions;
					Table[NewR][NewC] = 1;
					Q.push({ NewR,NewC,true });
				}
			}

			if (Table[NewR][NewC] == 1)
				Union(R * N + C, NewR * N + NewC);
		}
	}
}

void Solve()
{
	InitialBfs();

	int T{ 0 };

	if (bEnd)
	{
		cout << T;
		return;
	}

	while (true)
	{
		Bfs();

		++T;

		if (bEnd)
			break;
	}

	cout << T;
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