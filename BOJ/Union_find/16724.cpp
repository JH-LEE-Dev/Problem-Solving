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
using Vertex = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int N, M;
vector<vector<char>> Table(MAX, vector<char>(MAX));
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));
vector<int> Parent(MAX* MAX, -1);
vector<vector<int>> Idx(MAX, vector<int>(MAX, 0));
vector<int> Rank(MAX* MAX, 1);

//R,L,D,U
//©Л,аб,го,╩С
vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

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

			++Cnt;
		}
	}
}

int Find(int U)
{
	if (Parent[U] == U)
		return Parent[U];

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

void Bfs(int Row, int Col)
{
	queue <Vertex> Q;
	Q.push({ Row,Col });
	Visited[Row][Col] = true;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<0>(Cur) };
		auto C{ get<1>(Cur) };

		auto NewR{ R };
		auto NewC{ C };

		switch (Table[R][C])
		{
		case 'R':
		{
			NewR = R + Dir_Row[0];
			NewC = C + Dir_Col[0];
			break;
		}
		case 'L':
		{
			NewR = R + Dir_Row[1];
			NewC = C + Dir_Col[1];
			break;
		}
		case 'D':
		{
			NewR = R + Dir_Row[2];
			NewC = C + Dir_Col[2];
			break;
		}
		case 'U':
		{
			NewR = R + Dir_Row[3];
			NewC = C + Dir_Col[3];
			break;
		}
		}

		if (Visited[NewR][NewC] == false)
		{
			Visited[NewR][NewC] = true;
			Q.push({ NewR,NewC });

			Merge(Idx[R][C], Idx[NewR][NewC]);
		}
		else
		{
			Merge(Idx[R][C], Idx[NewR][NewC]);
		}
	}
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (Visited[i][j] == false)
			{
				Bfs(i, j);
			}
		}
	}

	set<int> Result;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			int Par{ Find(Parent[Idx[i][j]]) };

			if (Result.find(Par) == Result.end())
			{
				Result.insert(Par);
			}
		}
	}

	cout << Result.size();
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