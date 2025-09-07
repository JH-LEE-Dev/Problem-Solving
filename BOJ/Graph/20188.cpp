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
using LL = long long;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX	300'001

int N;
vector<vector<int>> Edges(MAX, vector<int>());
vector<bool> Visited(MAX, false);
LL Result;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N - 1; ++i)
	{
		int Src, Dst;

		cin >> Src >> Dst;

		Edges[Src].push_back(Dst);
		Edges[Dst].push_back(Src);
	}
}

LL Dfs(int Src)
{
	Visited[Src] = true;
	LL Cnt{ 1 };

	for (auto& Dst : Edges[Src])
	{
		if (Visited[Dst] == false)
			Cnt += Dfs(Dst);
	}

	if (Src != 1)
	{
		LL InnerCnt{ Cnt * (Cnt - 1) / 2 };
		LL Inner_OuterCnt{ Cnt * (N - Cnt) };
		Result += InnerCnt;
		Result += Inner_OuterCnt;
	}

	return Cnt;
}

void Solve()
{
	Dfs(1);

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