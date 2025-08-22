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
#define MAX 200'001

int N;
vector<int> Jump;
vector<int> Wait;
vector<LL> Dist;

vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());

void Input()
{
	cin >> N;

	Jump.resize(N + 2);
	Wait.resize(N + 2);
	Dist.resize(N + 2, INF);

	for (int i{ 1 }; i <= N; ++i)
	{
		cin >> Jump[i];
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		cin >> Wait[i];
	}
}

void GenerateGraph()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		int LeftPoint{ max(0,i - Jump[i]) };
		int RightPoint{ min(N + 1,i + Jump[i]) };

		Edges[LeftPoint].push_back({ i,Wait[i] });
		Edges[RightPoint].push_back({ i,Wait[i] });
	}
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	Dist[0] = 0;
	Dist[N + 1] = 0;
	PQ.push({ 0,0 });
	PQ.push({ 0,N + 1 });

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
	GenerateGraph();
	Dijkstra();

	for (int i{ 1 }; i <= N; ++i)
	{
		cout << Dist[i] << ' ';
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