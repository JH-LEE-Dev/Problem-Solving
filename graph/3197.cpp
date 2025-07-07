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
#define MAX 1'501

int N, M;
vector<vector<char>> Table(MAX, vector<char>(MAX, '.'));
vector<int> Rank(MAX* MAX, 0);
vector<int> Parent(MAX* MAX, 0);
vector<vector<int>> Idx(MAX, vector<int>(MAX, 0));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

pair<int, int> S{ -1,-1 };
pair<int, int> E{ -1 ,-1 };
queue<pair<int, int>> Q_Merge;
queue<pair<int, int>> Q_Melt;

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

	int Cnt{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];
			Parent[Cnt] = Cnt;
			Idx[i][j] = Cnt;

			if (Table[i][j] == 'L')
			{
				if (S.first == -1)
				{
					S.first = i;
					S.second = j;
				}
				else
				{
					E.first = i;
					E.second = j;
				}
				Q_Merge.push({ i,j });
			}

			if (Table[i][j] == '.')
				Q_Merge.push({ i,j });

			++Cnt;
		}
	}
}

int Find(int U)
{
	if (Parent[U] == U)
		return U;

	return Parent[U] = Find(Parent[U]);
}

void Merge(int U, int V)
{
	int Par_U{ Find(U) };
	int Par_V{ Find(V) };

	if (Par_U == Par_V)
		return;

	if (Rank[Par_U] > Rank[Par_V])
		swap(Par_U, Par_V);

	Parent[Par_U] = Par_V;

	if (Rank[Par_U] == Rank[Par_V])
		++Rank[Par_V];
}

void Bfs_Merge()
{
	while (Q_Merge.empty() == false)
	{
		auto Cur{ Q_Merge.front() };
		Q_Merge.pop();
		Q_Melt.push(Cur);

		auto R{ Cur.first };
		auto C{ Cur.second };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] != 'X')
			{
				Merge(Idx[R][C], Idx[NewR][NewC]);
			}
		}
	}
}

void Bfs_Melt()
{
	while (Q_Melt.empty() == false)
	{
		auto Cur{ Q_Melt.front() };
		Q_Melt.pop();

		auto R{ get<0>(Cur) };
		auto C{ get<1>(Cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] == 'X')
			{
				Table[NewR][NewC] = '.';
				Q_Merge.push({ NewR,NewC });
			}
		}
	}
}

void Solve()
{
	int Cnt{ 0 };

	while (true)
	{
		Bfs_Merge();

		if (Find(Idx[S.first][S.second]) == Find(Idx[E.first][E.second]))
		{
			cout << Cnt;
			return;
		}

		Bfs_Melt();

		++Cnt;
	}
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