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
#define MAX 51

int N;
vector<vector<int>> Edges(MAX, vector<int>());
vector<vector<char>> Table(MAX, vector<char>(MAX, 'N'));
vector<vector<int>> EdgesForCount(MAX, vector<int>());
vector<int> ClusterIdx(MAX, 0);
vector<bool> Visited(MAX, false);
int ClusterCnt{ 0 };
int SurplusEdgeCnt{ 0 };
bool bCycle{ false };
int EdgeCount{ 0 };
int VertexCount{ 0 };

void Input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

void Dfs(int Parent, int V, int Idx)
{
	ClusterIdx[V] = Idx;
	Visited[V] = true;
	++VertexCount;
	EdgeCount += EdgesForCount[V].size();

	for (auto& Dst : Edges[V])
	{
		if (Visited[Dst] == false)
		{
			Dfs(V, Dst, Idx);
		}
		else if (Dst != Parent)
		{
			bCycle = true;
		}
	}
}

void Solve()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			if (Table[i][j] == 'Y')
				Edges[i].push_back(j);
		}
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ i }; j <= N; ++j)
		{
			if (j == i)
				continue;

			if (Table[i][j] == 'Y')
				EdgesForCount[i].push_back(j);
		}
	}

	bool bValid{ true };
	int TotalVertexCount{ 0 };

	for (int i{ 1 }; i <= N; ++i)
	{
		if (Visited[i] == false)
		{
			Dfs(i, i, ClusterCnt);
			++ClusterCnt;

			bCycle = false;
			SurplusEdgeCnt += (EdgeCount - (VertexCount - 1));
			TotalVertexCount += VertexCount;
			EdgeCount = 0;
			VertexCount = 0;

			if (Edges[i].size() == 0)
			{
				bValid = false;
			}
		}
	}

	if (TotalVertexCount == 1 && Edges[1].size() == 0)
	{
		cout << 0;
		return;
	}

	if (bValid == false)
	{
		cout << -1;
		return;
	}

	if (ClusterCnt - 1 > SurplusEdgeCnt)
		cout << -1;
	else
		cout << ClusterCnt - 1;
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