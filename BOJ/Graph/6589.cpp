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
using Vertex = tuple<int, string>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 201

int N, M;
map<string, map<string, int>> Edges;
string Start, End;
map<string, int> Dist;
bool bEnd{ false };

void Input()
{
	Edges.clear();
	Dist.clear();

	cin >> N >> M;

	if (N == 0 && M == 0)
	{
		bEnd = true;
		return;
	}

	for (int i{ 0 }; i < M; ++i)
	{
		string Src, Dst;
		int W;

		cin >> Src >> Dst >> W;

		Edges[Src][Dst] = W;
		Edges[Dst][Src] = W;
	}

	cin >> Start >> End;
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,Start });
	Dist[Start] = 0;

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
			auto NewDist{ min(W,CurDist) };

			if (Src == Start)
				NewDist = W;

			if (Dist.find(Dst) == Dist.end())
			{
				Dist[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
			}
			else
			{
				if (Dist[Dst] < NewDist)
				{
					Dist[Dst] = NewDist;
					PQ.push({ NewDist,Dst });
				}
			}
		}
	}
}

void Solve()
{
	int i{ 1 };

	while (true)
	{
		Input();

		if (bEnd == true)
			return;

		Dijkstra();

		cout << "Scenario #" << i << endl;
		cout << Dist[End] << " tons" << endl;
		cout << endl;

		++i;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}