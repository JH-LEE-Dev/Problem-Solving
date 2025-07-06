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
#define MAX 2'001

int N, R, D, M;
vector<vector<pair<int, int>>>Edges(MAX, vector<pair<int, int>>());
vector<int> Dist(MAX, INF);

void Input()
{
	cin >> N >> R >> D >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int H, T, E1, E2;

		cin >> H >> T >> E1 >> E2;

		for (int j{ 0 }; j <= N - H; ++j)
		{
			Edges[E1 + j].push_back({ E2 + j,T });
			Edges[E2 + j].push_back({ E1 + j,T });
		}
	}
}

void Dijkstra(int Start)
{
	priority_queue <Vertex, vector<Vertex>, greater<Vertex>> PQ;
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

		if (Src == D)
		{
			cout << CurDist;
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

	cout << -1;
}

void Solve()
{
	Dijkstra(R);
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