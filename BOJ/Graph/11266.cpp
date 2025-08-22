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

int N, M;
vector<vector<int>> Edges(MAX, vector<int>());
vector<int> Order(MAX, -1);
set<int> Result;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst;
		cin >> Src >> Dst;

		Edges[Src].push_back(Dst);
		Edges[Dst].push_back(Src);
	}
}

int Dfs(bool bRoot, int Src, int CurOrder)
{
	int OutDegree{ 0 };
	Order[Src] = CurOrder + 1;
	int Ret{ INF };

	for (auto& Dst : Edges[Src])
	{
		if (Order[Dst] != -1)
		{
			Ret = min(Ret, Order[Dst]);
			continue;
		}

		++OutDegree;
		int NxtMinOrder{ Dfs(false, Dst, Order[Src]) };

		if (bRoot == false && NxtMinOrder >= Order[Src])
			Result.insert(Src);

		Ret = min(NxtMinOrder, Ret);
	}

	if (bRoot == true)
	{
		if (OutDegree >= 2)
			Result.insert(Src);
	}

	return Ret;
}

void Solve()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		if (Order[i] == -1)
			Dfs(true, i, Order[i]);
	}

	cout << Result.size() << endl;

	for (auto& V : Result)
	{
		cout << V << ' ';
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