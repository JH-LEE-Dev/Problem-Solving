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
#define MAX 100'01

bool IsValid{ true };

int N, M, S, C;
vector<vector<pair<int, int>>> Edges;

void Input()
{
	cin >> N >> M >> S >> C;

	if (N == 0 && M == 0 && S == 0 && C == 0)
	{
		IsValid = false;
		return;
	}

	Edges = vector<vector<pair<int, int>>>(MAX, vector<pair<int, int>>());

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
	}
}

void Dijkstra()
{
	vector<int> Dist(MAX, INF);

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,S });
	Dist[S] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src] < CurDist)
			continue;

		if (Src == C)
		{
			cout << CurDist << endl;
			return;
		}

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
}

void Solve()
{
	while (true)
	{
		Input();

		if (IsValid == false)
			return;

		Dijkstra();
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