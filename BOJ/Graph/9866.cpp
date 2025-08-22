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
using Vertex = tuple<LL, int>;

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 20'001

int N, M, K, Q;
vector<vector<LL>> Dist(MAX, vector<LL>(201, INF));
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
map<int, int> MyMap;

void Input()
{
	cin >> N >> M >> K >> Q;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int Temp;

		cin >> Temp;
		MyMap[Temp] = i;
	}
}

void Dijkstra(int Start, int Idx)
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,Start });
	Dist[Start][Idx] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src][Idx] < CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };

			if (Dist[Dst][Idx] > NewDist)
			{
				Dist[Dst][Idx] = NewDist;
				PQ.push({ NewDist,Dst });
			}
		}
	}
}

void Solve()
{
	for (auto& V : MyMap)
	{
		Dijkstra(V.first, V.second);
	}

	LL Cnt{ 0 };
	LL Total{ 0 };

	for (int i{ 0 }; i < Q; ++i)
	{
		int Start, End;

		cin >> Start >> End;

		auto Result{ INF };

		for (auto& Edge : Edges[Start])
		{
			auto Dst{ Edge.first };
			LL W{ Edge.second };

			if (MyMap.find(Start) != MyMap.end())
			{
				Result = min(Result, Dist[End][MyMap[Start]]);
			}
			else
			{
				if (Dist[End][MyMap[Dst]] != INF)
					Result = min(Result, W + Dist[End][MyMap[Dst]]);
			}
		}

		if (Result != INF)
		{
			++Cnt;
			Total += Result;
		}
	}

	cout << Cnt << endl;
	cout << Total;
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