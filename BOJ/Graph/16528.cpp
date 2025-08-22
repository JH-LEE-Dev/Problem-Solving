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
using State = tuple<LL, LL, int, int>;

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 10'001

int N, M;
vector<vector<tuple<int, int, int>>> Edges(MAX, vector<tuple<int, int, int>>());
vector<LL> Dist(MAX, INF);
LL Result;
set<pair<int, int>> ResultEdges;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W, C;
		cin >> Src >> Dst >> W >> C;

		Edges[Src].push_back({ C,W,Dst });
		Edges[Dst].push_back({ C,W,Src });
	}
}

void Dijkstra()
{
	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ 0,0,0,1 });
	Dist[1] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<3>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurC{ get<1>(Cur) };
		auto PrevC{ get<2>(Cur) };

		if (Dist[Src] < CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ get<2>(Edge) };
			auto W{ get<1>(Edge) };
			auto C{ get<0>(Edge) };
			auto NewDist{ CurDist + W };
			auto NewC{ CurC + C };

			if (Dist[Dst] > NewDist)
			{
				Dist[Dst] = NewDist;
				PQ.push({ NewDist,NewC,C,Dst });
			}
		}
	}
}

void Dfs(int Src)
{
	if (Src == 1)
		return;

	for (auto& Edge : Edges[Src])
	{
		auto Dst{ get<2>(Edge) };
		auto W{ get<1>(Edge) };
		auto C{ get<0>(Edge) };

		if (Dist[Dst] + W == Dist[Src])
		{
			int TempSrc{ Src };
			int TempDst{ Dst };

			if (TempSrc > TempDst)
				swap(TempSrc, TempDst);

			if (ResultEdges.find({ TempSrc,TempDst }) == ResultEdges.end())
			{
				ResultEdges.insert({ TempSrc,TempDst });
				Result += C;
			}

			Dfs(Dst);

			break;
		}
	}
}

void Solve()
{
	Dijkstra();

	for (int i{ 1 }; i <= N; ++i)
	{
		sort(Edges[i].begin(), Edges[i].end());
	}

	for (int i{ 2 }; i <= N; ++i)
	{
		Dfs(i);
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