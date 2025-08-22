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
#define MAX 5'001

int N, M;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<priority_queue<int>> Dist(MAX, priority_queue<int>());

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

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	Dist[1].push(0);
	PQ.push({ 0,1 });

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src].top() < CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };

			if (Dist[Dst].size() >= 2)
			{
				if (Dist[Dst].top() > NewDist)
				{
					Dist[Dst].pop();
					Dist[Dst].push(NewDist);
					PQ.push({ NewDist,Dst });
				}
			}
			else
			{
				Dist[Dst].push(NewDist);
				PQ.push({ NewDist,Dst });
			}
		}
	}
}

void Solve()
{
	Dijkstra();

	cout << Dist[N].top();
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