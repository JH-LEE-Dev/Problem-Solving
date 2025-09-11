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
using State = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 50'001

int N, M, B;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<pair<int, int>> Query;
vector<int> Dist(MAX, INF);

void Input()
{
	cin >> N >> M >> B;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;
		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });
	}

	for (int i{ 0 }; i < B; ++i)
	{
		int Src, Dst;
		cin >> Src >> Dst;

		Query.push_back({ Src,Dst });
	}
}

void Dijkstra()
{
	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ 0,1 });
	Dist[1] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto [CurDist, Src] {Cur};

		if (Dist[Src] < CurDist)
			continue;

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
	Dijkstra();

	for (int i{ 0 }; i < B; ++i)
	{
		auto [Src, Dst] {Query[i]};

		cout << Dist[Src] + Dist[Dst] << endl;
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