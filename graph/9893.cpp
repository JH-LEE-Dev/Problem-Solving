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
#define MAX 101

int N, M;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<pair<int, int>> Dist(MAX, { INF,INF });

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;
		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
	}
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,0,0 });
	Dist[0] = { 0,0 };

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<2>(Cur) };
		auto CurCnt{ get<0>(Cur) };
		auto CurDist{ get<1>(Cur) };

		if (Dist[Src] < make_pair(CurCnt, CurDist))
			continue;

		if (Src == 1)
		{
			cout << CurDist;
			return;
		}

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };
			auto NewCnt{ CurCnt + 1 };

			if (Dist[Dst] > make_pair(NewCnt, NewDist))
			{
				Dist[Dst] = { NewCnt,NewDist };
				PQ.push({ NewCnt,NewDist,Dst });
			}
		}
	}
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