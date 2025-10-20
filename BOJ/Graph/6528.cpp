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
using State = tuple<double, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N, M;
vector<vector<pair<int, double>>> Edges;
vector<double> Dist;
bool bValid{ true };

void Input()
{
	cin >> N;

	if (N == 0)
	{
		bValid = false;
		return;
	}

	cin >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst;
		double W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W * 0.01 });
		Edges[Dst].push_back({ Src,W * 0.01 });
	}
}

void Dijkstra()
{
	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ -INF,1 });
	Dist[1] = -INF;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto [CurDist, Src] {Cur};

		if (Dist[Src] < CurDist)
			continue;

		for (const auto& Edge : Edges[Src])
		{
			auto [Dst, W] {Edge};

			auto NewDist{ W * CurDist };

			if (Src == 1)
				NewDist = -W;

			if (Dist[Dst] > NewDist)
			{
				Dist[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
			}
		}
	}

	cout << fixed << setprecision(6) << -Dist[N] * 100 << " percent" << endl;
}

void Solve()
{
	while (true)
	{
		Edges = vector<vector<pair<int, double>>>(MAX, vector<pair<int, double>>());
		Dist = vector<double>(MAX, INF);

		Input();

		if (bValid == false)
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