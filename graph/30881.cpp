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
using Vertex = tuple <LL, int>;

#define endl '\n'
#define INF (LL)1e18+1
#define MAX 200'001

int T, N, M;
vector< vector<vector<tuple<int, LL, bool>>>> Edges;
vector<vector<LL>> DistEdge(100'001, vector<LL>(2, INF));
set<pair<int, int>> NotValidGraphs;

void Input(int Idx)
{
	cin >> N >> M;

	Edges[Idx].resize(N + 1);

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Idx][Src].push_back({ Dst,W,true });

		if (W < 0)
			Edges[Idx][Dst].push_back({ Src,W,false });
	}
}

LL Dijkstra(int Idx, bool CurDir)
{
	vector<LL> Dist(Edges[Idx].size(), INF);
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;

	if (CurDir == true)
	{
		PQ.push({ 0,1 });
		Dist[1] = 0;
	}
	else
	{
		PQ.push({ 0,2 });
		Dist[2] = 0;
	}

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src] < CurDist)
			continue;

		if (CurDir == true)
		{
			if (Src == 2)
			{
				return CurDist;
			}
		}
		else
		{
			if (Src == 1)
			{
				return CurDist;
			}
		}

		for (auto& Edge : Edges[Idx][Src])
		{
			auto Dst{ get<0>(Edge) };
			auto W{ get<1>(Edge) };
			auto Dir{ get<2>(Edge) };

			if (W < 0)
			{
				if (NotValidGraphs.find({ abs(W),Dir }) != NotValidGraphs.end())
					continue;

				if (DistEdge[abs(W)][Dir] == INF)
				{
					auto Weight{ Dijkstra(abs(W),Dir) };

					if (Weight == INF)
					{
						NotValidGraphs.insert({ abs(W),Dir });
						continue;
					}

					DistEdge[abs(W)][Dir] = Weight;
					W = Weight;
				}
				else
				{
					W = DistEdge[abs(W)][Dir];
				}
			}

			auto NewDist{ CurDist + W };

			if (NewDist < INF)
			{
				if (Dist[Dst] > NewDist)
				{
					Dist[Dst] = NewDist;
					PQ.push({ NewDist,Dst });
				}
			}
		}
	}

	return INF;
}

void Solve()
{
	cin >> T;

	Edges.resize(T + 1);
	int Idx{ 1 };

	while (T != 0)
	{
		Input(Idx);

		++Idx;
		--T;
	}

	DistEdge[Idx - 1][true] = Dijkstra(Idx - 1, true);

	if (DistEdge[Idx - 1][true] == INF || DistEdge[Idx - 1][true] > LL(1e18))
		cout << -1;
	else
		cout << DistEdge[Idx - 1][true];
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}