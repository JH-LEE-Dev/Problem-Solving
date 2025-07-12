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
#define MAX 50'001

int N, M, T;
vector<vector<tuple<int, LL, LL>>> Edges(MAX, vector<tuple<int, LL, LL>>());

LL Result{ INF };

void Input()
{
	cin >> N >> M >> T;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W, S;

		cin >> Src >> Dst >> W >> S;

		Edges[Src].push_back({ Dst,W,S });
		Edges[Dst].push_back({ Src,W,S });
	}
}

bool Dijkstra(LL Limit)
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
			auto Dst{ get<0>(Edge) };
			auto W{ get<1>(Edge) };
			auto S{ get<2>(Edge) };
			auto NewDist{ CurDist + W };

			if (S > Limit)
			{
				NewDist += (S - Limit);
				S = Limit;
			}

			if (NewDist > T)
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

void Bsearch()
{
	LL Left{ 0 };
	LL Right{ 1'000'000'000 };

	while (Left <= Right)
	{
		LL Middle{ (Left + Right) / 2 };

		bool bCanReach{ Dijkstra(Middle) };

		if (bCanReach)
		{
			Result = min(Result, Middle);
			Right = Middle - 1;
		}
		else
		{
			Left = Middle + 1;
		}
	}
}

void Solve()
{
	Bsearch();

	if (Result == INF)
		cout << -1;
	else
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