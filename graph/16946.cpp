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
#define MAX 1'001

int N, M;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<int>> CntTable(MAX, vector<int>(MAX, 0));
vector<vector<int>> Idx(MAX, vector<int>(MAX, 0));
vector<int> Parent(MAX* MAX, -1);
vector<int> Rank(MAX* MAX, 1);

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };
vector<int> Cnt(MAX* MAX, 1);

vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));

void Input()
{
	cin >> N >> M;

	int IdxCount{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		string Str;
		cin >> Str;

		for (int j{ 0 }; j < Str.length(); ++j)
		{
			Table[i][j] = Str[j] - '0';

			Idx[i][j] = IdxCount;
			Parent[IdxCount] = IdxCount;

			++IdxCount;
		}
	}
}

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0 || Table[R][C] == 1)
		return false;
	else
		return true;
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
	Cnt[Par_V] += Cnt[Par_U];

	if (Rank[Par_U] == Rank[Par_V])
		++Rank[Par_V];
}

void Bfs(pair<int, int> Start)
{
	queue<pair<int, int>> Q;
	Q.push({ Start.first,Start.second });
	Visited[Start.first][Start.second] = true;

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

			if (Visited[NewR][NewC] == false)
			{
				Visited[NewR][NewC] = true;
				Q.push({ NewR,NewC });

				Merge(Idx[R][C], Idx[NewR][NewC]);
			}
		}
	}
}

void GatherCnt(pair<int, int> Start)
{
	int TempCnt{ 1 };
	set<int> ParentSet;

	for (int i{ 0 }; i < 4; ++i)
	{
		auto NewR{ Start.first + Dir_Row[i] };
		auto NewC{ Start.second + Dir_Col[i] };

		if (IsValid(NewR, NewC) == false)
			continue;

		ParentSet.insert(Find(Idx[NewR][NewC]));
	}

	for (const auto& Par : ParentSet)
	{
		TempCnt += Cnt[Par];
	}

	CntTable[Start.first][Start.second] = TempCnt % 10;
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (Table[i][j] == 1)
				continue;

			if (Visited[i][j] == false)
				Bfs({ i,j });
		}
	}

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (Table[i][j] != 1)
			{
				cout << 0;
				continue;
			}

			GatherCnt({ i,j });

			cout << CntTable[i][j];
		}

		cout << endl;
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