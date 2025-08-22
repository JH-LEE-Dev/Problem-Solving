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

int N, M;
vector<vector<int>> Edges(MAX, vector<int>());
vector<pair<int, int>> Result;
vector<int> VisitOrder(MAX, INF);

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

int Dfs(int Src, int From, int Order)
{
	VisitOrder[Src] = Order;

	int NxtOrder{ Order };

	for (auto& Dst : Edges[Src])
	{
		if (VisitOrder[Dst] == INF)
		{
			NxtOrder = min(NxtOrder, Dfs(Dst, Src, Order + 1));
		}
		else if (Dst != From)
		{
			NxtOrder = min(NxtOrder, VisitOrder[Dst]);
		}
	}

	if (NxtOrder >= Order && From != Src)
	{
		if (From > Src)
			swap(From, Src);

		Result.push_back({ From,Src });
	}

	return NxtOrder;
}

void Solve()
{
	Dfs(1, 1, 0);

	cout << Result.size() << endl;

	sort(Result.begin(), Result.end());

	for (auto& Edge : Result)
	{
		cout << Edge.first << ' ' << Edge.second << endl;
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