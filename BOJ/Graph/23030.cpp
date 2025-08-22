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
using Vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 51

int N, M, K;
vector<int> VertexCnt(11, 0);
vector<vector<vector<pair<int, int>>>> Edges(11, vector<vector<pair<int, int>>>(MAX, vector<pair<int, int>>()));
vector<vector<int>> Dist(11, vector<int>(MAX, INF));

void Input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		cin >> VertexCnt[i];
	}

	cin >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int SrcIdx, SrcVertex, DstIdx, DstVertex;

		cin >> SrcIdx >> SrcVertex >> DstIdx >> DstVertex;

		Edges[SrcIdx][SrcVertex].push_back({ DstIdx,DstVertex });
		Edges[DstIdx][DstVertex].push_back({ SrcIdx,SrcVertex });
	}
}

void Dijkstra(int StartIdx, int StartVertex, int EndIdx, int EndVertex, int T)
{
	priority_queue< Vertex, vector< Vertex>, greater<Vertex>>PQ;
	Dist[StartIdx][StartVertex] = 0;
	PQ.push({ 0,StartIdx,StartVertex });

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto SrcIdx{ get<1>(Cur) };
		auto SrcVertex{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[SrcIdx][SrcVertex] < CurDist)
			continue;

		if (SrcIdx == EndIdx && SrcVertex == EndVertex)
		{
			cout << CurDist << endl;
			return;
		}

		for (int i{ 1 }; i <= VertexCnt[SrcIdx]; ++i)
		{
			auto W{ abs(SrcVertex - i) };
			auto NewDist{ CurDist + W };

			if (SrcIdx == EndIdx && i == EndVertex)
			{
				if (Dist[SrcIdx][i] > NewDist)
				{
					Dist[SrcIdx][i] = NewDist;
					PQ.push({ NewDist,SrcIdx,i });
				}

				continue;
			}
			else if (Edges[SrcIdx][i].empty())
				continue;

			if (Dist[SrcIdx][i] > NewDist)
			{
				Dist[SrcIdx][i] = NewDist;
				PQ.push({ NewDist,SrcIdx,i });
			}
		}

		for (auto& Edge : Edges[SrcIdx][SrcVertex])
		{
			auto DstIdx{ Edge.first };
			auto DstVertex{ Edge.second };
			auto W{ T };

			auto NewDist{ CurDist + T };

			if (Dist[DstIdx][DstVertex] > NewDist)
			{
				Dist[DstIdx][DstVertex] = NewDist;
				PQ.push({ NewDist,DstIdx,DstVertex });
			}
		}
	}
}

void Solve()
{
	cin >> K;

	for (int i{ 0 }; i < K; ++i)
	{
		Dist = vector<vector<int>>(11, vector<int>(MAX, INF));

		int T, SrcIdx, SrcVertex, DstIdx, DstVertex;
		cin >> T >> SrcIdx >> SrcVertex >> DstIdx >> DstVertex;

		Dijkstra(SrcIdx, SrcVertex, DstIdx, DstVertex, T);
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