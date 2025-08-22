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
#define MAX 1'001

int N;
vector<vector<int>> Edges(MAX, vector<int>());
vector<int> Dist(MAX, INF);
vector<int> Weights(MAX, INF);

void Input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		int W, K;

		cin >> W >> K;

		Weights[i] = W;

		for (int j{ 0 }; j < K; ++j)
		{
			int Dst;
			cin >> Dst;

			Edges[i].push_back(Dst);
		}
	}
}

void Dijkstra()
{
	int Result{ 0 };

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	Dist[1] = Weights[1];
	PQ.push({ Weights[1],1 });

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src] < CurDist)
			continue;

		Result = max(Result, CurDist);

		for (auto& Dst : Edges[Src])
		{
			auto W{ Weights[Dst] };
			auto NewDist{ CurDist + W };

			if (Dist[Dst] > NewDist)
			{
				Dist[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
			}
		}
	}

	cout << Result;
}

void Solve()
{
	Dijkstra();
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