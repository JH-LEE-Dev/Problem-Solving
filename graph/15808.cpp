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
using Vertex = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int N, P, Q;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<pair<int, int>> Parr;
vector<pair<int, int>> Qarr;

int Result{ -INF };

void Input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			int W;
			cin >> W;

			if (W != 0)
			{
				Edges[i].push_back({ j,W });
			}
		}
	}

	cin >> P >> Q;

	for (int i{ 1 }; i <= P; ++i)
	{
		int V, W;
		cin >> V >> W;

		Parr.push_back({ V,W });
	}

	for (int i{ 1 }; i <= Q; ++i)
	{
		int V, W;
		cin >> V >> W;

		Qarr.push_back({ V,W });
	}
}

void Dijkstra(pair<int, int>Start, int Type)
{
	vector<int> Dist(MAX, INF);

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,Start.first });
	Dist[Start.first] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src] < CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };

			if (Dist[Dst] > NewDist)
			{
				Dist[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
			}
		}
	}

	if (Type == 0)
	{
		for (auto& Temp : Qarr)
		{
			Result = max(Result, Start.second + Temp.second - Dist[Temp.first]);
		}
	}
	else
	{
		for (auto& Temp : Parr)
		{
			Result = max(Result, Start.second + Temp.second - Dist[Temp.first]);
		}
	}
}

void Solve()
{
	int Type{ 0 };

	if (P > Q)
		Type = 1;

	if (Type == 0)
	{
		for (int i{ 0 }; i < Parr.size(); ++i)
		{
			Dijkstra(Parr[i], 0);
		}
	}
	else
	{
		for (int i{ 0 }; i < Qarr.size(); ++i)
		{
			Dijkstra(Qarr[i], 1);
		}
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