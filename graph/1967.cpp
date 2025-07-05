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
#define MAX 10'001

int N;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<int> Dist(MAX, -1);
vector<bool> Visited(MAX, false);

int Result{ 0 };

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N - 1; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });
	}
}

void Dfs(int V, int CurDist)
{
	Visited[V] = true;

	for (auto& Edge : Edges[V])
	{
		auto Dst{ Edge.first };
		auto W{ Edge.second };

		if (Visited[Dst] == false)
		{
			Result = max(Result, CurDist + W);
			Dfs(Dst, CurDist + W);
		}
	}
}

void Solve()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		Visited = vector<bool>(MAX, false);

		Dfs(i, 0);
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