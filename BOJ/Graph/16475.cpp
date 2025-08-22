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
using Vertex = tuple<int, int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 10'001

int N, M, K, L, P, S, E;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<vector<pair<int, int>>> Edges_Off(MAX, vector<pair<int, int>>());
vector<vector<pair<int, int>>> Edges_On(MAX, vector<pair<int, int>>());
set<int> Traps;
vector<vector<vector<int>>> Dist(MAX, vector<vector<int>>(11, vector<int>(2, INF)));

void Input()
{
	cin >> N >> M >> K >> L >> P;

	for (int i{ 0 }; i < K; ++i)
	{
		int Temp;
		cin >> Temp;

		Traps.insert(Temp);
	}

	for (int i{ 0 }; i < M - L; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
	}

	for (int i{ 0 }; i < L; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges_Off[Src].push_back({ Dst,W });
		Edges_On[Dst].push_back({ Src,W });
	}

	cin >> S >> E;
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,S,0,0 });
	Dist[S][0][0] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurCnt{ get<2>(Cur) };
		auto CurType{ get<3>(Cur) };

		if (Dist[Src][CurCnt][CurType] < CurDist)
			continue;

		if (Src == E)
		{
			cout << CurDist;
			return;
		}

		if (CurType == 0)
		{
			for (auto& Edge : Edges_Off[Src])
			{
				auto Dst{ Edge.first };
				auto W{ Edge.second };
				auto NewDist{ CurDist + W };
				auto NewCnt{ CurCnt };
				auto NewType{ CurType };

				if (Traps.find(Dst) != Traps.end())
					++NewCnt;

				if (NewCnt >= P)
				{
					NewCnt = 0;
					NewType = 1 - NewType;
				}

				if (Dist[Dst][NewCnt][NewType] > NewDist)
				{
					Dist[Dst][NewCnt][NewType] = NewDist;
					PQ.push({ NewDist,Dst,NewCnt,NewType });
				}
			}
		}
		else
		{
			for (auto& Edge : Edges_On[Src])
			{
				auto Dst{ Edge.first };
				auto W{ Edge.second };
				auto NewDist{ CurDist + W };
				auto NewCnt{ CurCnt };
				auto NewType{ CurType };

				if (Traps.find(Dst) != Traps.end())
					++NewCnt;

				if (NewCnt >= P)
				{
					NewCnt = 0;
					NewType = 1 - NewType;
				}

				if (Dist[Dst][NewCnt][NewType] > NewDist)
				{
					Dist[Dst][NewCnt][NewType] = NewDist;
					PQ.push({ NewDist,Dst,NewCnt,NewType });
				}
			}
		}

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };
			auto NewCnt{ CurCnt };
			auto NewType{ CurType };

			if (Traps.find(Dst) != Traps.end())
				++NewCnt;

			if (NewCnt >= P)
			{
				NewCnt = 0;
				NewType = 1 - NewType;
			}

			if (Dist[Dst][NewCnt][NewType] > NewDist)
			{
				Dist[Dst][NewCnt][NewType] = NewDist;
				PQ.push({ NewDist,Dst,NewCnt,NewType });
			}
		}
	}

	cout << -1;
}

void Solve()
{
	Dijkstra();
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