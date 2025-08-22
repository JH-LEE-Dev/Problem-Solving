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

int T, N, P, M;
vector<vector<pair<int, int>>> Edges;
vector<pair<int, int>> Friends;
vector<vector<int>> Dist;

void Input()
{
	Dist = vector<vector<int>>(MAX, vector<int>(101, INF));
	Edges = vector<vector<pair<int, int>>>(MAX, vector<pair<int, int>>());
	Friends.clear();

	cin >> N >> P >> M;

	for (int i{ 0 }; i < P; ++i)
	{
		int V, W;

		cin >> V >> W;

		Friends.push_back({ V,W });
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int W, L;

		cin >> W >> L;

		vector<int> V;
		for (int j{ 0 }; j < L; ++j)
		{
			int Temp;
			cin >> Temp;

			V.push_back(Temp);
		}

		for (int j{ 1 }; j < V.size(); ++j)
		{
			Edges[V[j - 1]].push_back({ V[j],W });
			Edges[V[j]].push_back({ V[j - 1],W });
		}
	}
}

void Dijkstra(int Start, int Speed, int Idx)
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,Start });
	Dist[Start][Idx] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src][Idx] < CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + Speed * W };

			if (Dist[Dst][Idx] > NewDist)
			{
				Dist[Dst][Idx] = NewDist;
				PQ.push({ NewDist,Dst });
			}
		}
	}
}

void Solve()
{
	cin >> T;

	for (int i{ 0 }; i < T; ++i)
	{
		Input();

		for (int j{ 0 }; j < Friends.size(); ++j)
		{
			Dijkstra(Friends[j].first, Friends[j].second, j);
		}

		int Result{ INF };

		for (int j{ 1 }; j <= N; ++j)
		{
			int Max{ -1 };

			for (int k{ 0 }; k < Friends.size(); ++k)
			{
				Max = max(Max, Dist[j][k]);
			}

			Result = min(Result, Max);
		}

		if (Result == INF)
			cout << "Case #" << i + 1 << ": " << -1 << endl;
		else
			cout << "Case #" << i + 1 << ": " << Result << endl;
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