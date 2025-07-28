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
#define MAX 100'001

int N, M;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<int> Dist(MAX, INF);

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ W,Dst });
		Edges[Dst].push_back({ W,Src });
	}
}

void Dijkstra_Backward()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,N });
	Dist[N] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src] < CurDist)
			continue;

		if (Src == 1)
		{
			cout << CurDist << endl;
			return;
		}

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.second };
			auto W{ Edge.first };
			auto NewDist{ CurDist + 1 };

			if (Dist[Dst] > NewDist)
			{
				Dist[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
			}
		}
	}
}

void Dijkstra_Forward()
{
	map<int, int> Result;
	vector<int> Weights(MAX, INF);
	vector<int> MinWeights(MAX, INF);

	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> PQ;
	PQ.push({ 0,0,1 });

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<2>(Cur) };
		auto CurIdx{ get<0>(Cur) };
		auto CurW{ get<1>(Cur) };

		if (Weights[Src] < CurW || MinWeights[CurIdx] < CurW)
			continue;

		if (CurIdx != 0)
			Result[CurIdx] = CurW;

		if (Src == N)
			break;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.second };
			auto W{ Edge.first };

			if (Dist[Dst] + 1 == Dist[Src])
			{
				MinWeights[CurIdx + 1] = min(MinWeights[CurIdx + 1], W);

				if (Weights[Dst] > W)
				{
					Weights[Dst] = W;
					PQ.push({ CurIdx + 1,W,Dst });
				}
			}
		}
	}

	for (auto& V : Result)
	{
		cout << V.second << ' ';
	}
}

void Solve()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		sort(Edges[i].begin(), Edges[i].end());
	}

	Dijkstra_Backward();
	Dijkstra_Forward();
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