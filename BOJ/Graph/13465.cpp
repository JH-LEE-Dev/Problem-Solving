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
#define MAX 10'001

int N, M, X;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
LL Limit;
int MaxW;

void Input()
{
	cin >> N >> M >> X;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });

		MaxW = max(MaxW, W);
	}
}

void Dijkstra_First()
{
	vector<LL> Dist(MAX, INF);
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

		if (Src == N)
			break;

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

	Limit = Dist[N] + (Dist[N] * X) / 100;
}

bool Dijkstra_Second(int Longest)
{
	vector<LL> Dist(MAX, INF);
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

		if (Src == N)
			return true;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };

			if (NewDist > Limit || W > Longest)
				continue;

			if (Dist[Dst] > NewDist)
			{
				Dist[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
			}
		}
	}

	return false;
}

void Solve()
{
	Dijkstra_First();

	int Left{ 1 };
	int Right{ MaxW };
	int Result{ MaxW };

	while (Left <= Right)
	{
		int Middle{ (Left + Right) / 2 };

		if (Dijkstra_Second(Middle))
		{
			Right = Middle - 1;
			Result = min(Result, Middle);
		}
		else
			Left = Middle + 1;
	}

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