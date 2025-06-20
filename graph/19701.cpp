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
using Vertex = tuple<LL, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 100'001

int N, M;
vector<vector<tuple<int, int, int>>> Edges(MAX, vector<tuple<int, int, int>>());
vector<vector<int>> Dist(MAX, vector<int>(2, INF));

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W, K;
		cin >> Src >> Dst >> W >> K;

		Edges[Src].push_back({ Dst,W,K });
		Edges[Dst].push_back({ Src,W,K });
	}
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,0,1 });
	Dist[1][0] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurEat{ get<1>(Cur) };

		if (Dist[Src][CurEat] < CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ get<0>(Edge) };
			auto W{ get<1>(Edge) };
			auto K{ get<2>(Edge) };

			auto NewDist{ CurDist + W };

			if (CurEat == 0)
			{
				if (Dist[Dst][1] > NewDist - K)
				{
					Dist[Dst][1] = NewDist - K;
					PQ.push({ NewDist - K,1,Dst });
				}
			}

			if (Dist[Dst][CurEat] > NewDist)
			{
				Dist[Dst][CurEat] = NewDist;
				PQ.push({ NewDist,CurEat,Dst });
			}
		}
	}
}

void Solve()
{
	Dijkstra();

	for (int i{ 2 }; i <= N; ++i)
	{
		cout << min(Dist[i][0], Dist[i][1]) << endl;
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