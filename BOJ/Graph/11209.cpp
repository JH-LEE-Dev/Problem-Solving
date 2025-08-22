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
#define MAX 100'001

int S, T, N, M;
vector<vector<pair<int, LL>>> Edges_Forward(MAX, vector<pair<int, LL>>());
vector<vector<pair<int, LL>>> Edges_Backward(MAX, vector<pair<int, LL>>());
vector<LL> Dist(MAX, INF);
vector<int> Result;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges_Forward[Src].push_back({ Dst,W });
		Edges_Backward[Dst].push_back({ Src,W });
	}

	cin >> S >> T;
}

void Dijkstra()
{
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

		for (const auto& Edge : Edges_Forward[Src])
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

void Dijkstra_Backward()
{
	vector<bool> Visited(MAX, false);
	priority_queue<Vertex, vector<Vertex>, less<Vertex>> PQ;
	PQ.push({ 0,T });
	Visited[T] = false;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (PQ.empty())
			Result.push_back(Src);

		for (auto& Edge : Edges_Backward[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };

			if (Dist[Dst] + W == Dist[Src] && Visited[Dst] == false)
			{
				PQ.push({ Dist[Dst],Dst });
				Visited[Dst] = true;
			}
		}
	}
}

void Solve()
{
	Dijkstra();
	Dijkstra_Backward();

	sort(Result.begin(), Result.end());

	for (int i{ 0 }; i < Result.size(); ++i)
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