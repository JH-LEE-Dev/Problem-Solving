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
#define MAX 10'001

int N, M;
int Start, End;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<vector<pair<int, int>>> Edges_Reverse(MAX, vector<pair<int, int>>());
vector<int> Dist(MAX, -INF);
int Result;
vector<bool> Visited(MAX, false);

void Input()
{
	cin >> N >> M;
	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges_Reverse[Dst].push_back({ Src,W });
	}

	cin >> Start >> End;
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, less<Vertex>> PQ;
	PQ.push({ 0,Start });
	Dist[Start] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src] > CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };

			if (Dist[Dst] < NewDist)
			{
				Dist[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
			}
		}
	}
}

void Bfs()
{
	queue<int> Q;
	Q.push(End);
	Visited[End] = true;

	while (Q.empty() == false)
	{
		auto Src{ Q.front() };
		Q.pop();

		for (auto& Edge : Edges_Reverse[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };

			if (Dist[Dst] + W == Dist[Src])
			{
				if (Visited[Dst] == false)
				{
					Visited[Dst] = true;
					Q.push(Dst);
				}

				++Result;
			}
		}
	}
}

void Solve()
{
	Dijkstra();
	Bfs();

	cout << Dist[End] << endl;
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