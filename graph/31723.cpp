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
#define MAX 300'001

int N, M;
vector<vector<tuple<int, int, int>>> Edges(MAX, vector<tuple<int, int, int>>());
vector<vector<tuple<int, int, int>>> Edges_Reverse(MAX, vector<tuple<int, int, int>>());
vector<pair<int, int>> Parent(MAX, { INF,INF });
vector<LL> Dist(MAX, INF);
vector<int> Result(500'001, 1);
LL TotalDist;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W,i });
		Edges_Reverse[Dst].push_back({ Src,W,i });
	}
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,1 });
	Dist[1] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src] < CurDist)
			continue;

		TotalDist += CurDist;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ get<0>(Edge) };
			auto W{ get<1>(Edge) };
			auto NewDist{ CurDist + W };

			if (Dist[Dst] > NewDist)
			{
				Dist[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
				Parent[Dst] = { Src,1 };
			}
		}

		for (auto& Edge : Edges_Reverse[Src])
		{
			auto Dst{ get<0>(Edge) };
			auto W{ get<1>(Edge) };
			auto NewDist{ CurDist + 2 * W };

			if (Dist[Dst] > NewDist)
			{
				Dist[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
				Parent[Dst] = { Src,0 };
			}
		}
	}
}

void Bfs()
{
	queue<int> Q;
	Q.push(1);

	while (Q.empty() == false)
	{
		auto Src{ Q.front() };
		Q.pop();

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ get<0>(Edge) };
			auto Idx{ get<2>(Edge) };

			if (Parent[Dst].first == Src && Parent[Dst].second == 1)
			{
				Result[Idx] = 1;
				Q.push(Dst);
			}
		}

		for (auto& Edge : Edges_Reverse[Src])
		{
			auto Dst{ get<0>(Edge) };
			auto Idx{ get<2>(Edge) };

			if (Parent[Dst].first == Src && Parent[Dst].second == 0)
			{
				Result[Idx] = 0;
				Q.push(Dst);
			}
		}
	}
}

void Solve()
{
	Dijkstra();
	Bfs();

	cout << TotalDist << endl;

	for (int i{ 0 }; i < M; ++i)
	{
		cout << Result[i] << ' ';
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