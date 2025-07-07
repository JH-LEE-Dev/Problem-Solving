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
#define MAX 100'001

int N;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<bool> Visited(MAX, false);

int RandomMax;
int RandomStart;
int Result;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int Src;
		cin >> Src;

		while (true)
		{
			int Dst, W;
			cin >> Dst;

			if (Dst == -1)
				break;

			cin >> W;

			Edges[Src].push_back({ Dst,W });
			Edges[Dst].push_back({ Src,W });
		}
	}
}

void Dfs(int V, int CurDist)
{
	Visited[V] = true;

	if (RandomMax < CurDist)
	{
		RandomMax = CurDist;
		RandomStart = V;
	}

	for (auto& Edge : Edges[V])
	{
		auto Dst{ Edge.first };
		auto W{ Edge.second };

		if (Visited[Dst] == false)
		{
			Dfs(Dst, CurDist + W);
		}
	}
}

void Dfs_Result(int V, int CurDist)
{
	Visited[V] = true;

	Result = max(Result, CurDist);

	for (auto& Edge : Edges[V])
	{
		auto Dst{ Edge.first };
		auto W{ Edge.second };

		if (Visited[Dst] == false)
		{
			Dfs_Result(Dst, CurDist + W);
		}
	}
}

void Solve()
{
	Dfs(1, 0);

	Visited = vector<bool>(MAX, false);

	Dfs_Result(RandomStart, 0);

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