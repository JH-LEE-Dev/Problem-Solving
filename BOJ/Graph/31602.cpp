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
using State = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 100'001

int N, M;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<vector<int>> Dist_Reverse(MAX, vector<int>(2, INF));
vector<int> Dist_Forward(MAX, INF);
set<pair<int, int>> Path;
vector<int> Parent(MAX, -1);

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;
		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });
	}
}

void Dijkstra_Forward()
{
	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PQ;
	PQ.push({ 0,1 });
	Dist_Forward[1] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist_Forward[Src] < CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };

			if (Dist_Forward[Dst] > NewDist)
			{
				Dist_Forward[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
				Parent[Dst] = Src;
			}
		}
	}

	auto Cursor{ N };
	while (Cursor != -1)
	{
		int Cur{ Cursor };
		int Par{ Parent[Cur] };

		if (Par == -1)
			break;

		if (Cur > Par)
			swap(Cur, Par);

		Path.insert({ Cur,Par });
		Cursor = Parent[Cursor];
	}
}

void Dijkstra_Reverse()
{
	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ 0,0,N });
	Dist_Reverse[N][0] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurType{ get<1>(Cur) };

		if (Dist_Reverse[Src][CurType] < CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };
			auto NewType{ CurType };

			auto TempSrc{ Src };
			auto TempDst{ Dst };

			if (TempSrc > TempDst)
				swap(TempSrc, TempDst);

			if (Path.find({ TempSrc,TempDst }) == Path.end())
				NewType = 1;

			if (Dist_Reverse[Dst][NewType] > NewDist)
			{
				Dist_Reverse[Dst][NewType] = NewDist;
				PQ.push({ NewDist,NewType,Dst });
			}
		}
	}
}

void Solve()
{
	Dijkstra_Forward();
	Dijkstra_Reverse();

	if (Dist_Forward[N] == INF || Dist_Reverse[1][1] == INF)
		cout << -1;
	else
		cout << Dist_Forward[N] + Dist_Reverse[1][1];
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