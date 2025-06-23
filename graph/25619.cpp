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
using Vertex = tuple<double, int>;

#define endl '\n'
#define INF numeric_limits<double>::max()
#define MAX 200'001

int N, M;
double K;
vector<vector<pair<int, double>>> Edges(MAX, vector<pair<int, double>>());
vector<int> Result;
bool bCycle{ false };
vector<bool> Visited(MAX, false);
vector<double> Dist(MAX, INF);
int Cnt{ 0 };

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W1, W2;

		cin >> Src >> Dst >> W1 >> W2;

		Edges[Src].push_back({ Dst,((double)W1 + (double)W2) / 2 });
		Edges[Dst].push_back({ Src,((double)W1 + (double)W2) / 2 });
	}

	cin >> K;
}

void Bfs()
{
	queue<int> Q;
	Q.push(1);
	Visited[1] = true;

	while (Q.empty() == false)
	{
		auto Src{ Q.front() };
		Q.pop();

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ get<0>(Edge) };
			auto W{ get<1>(Edge) };

			if (W < 0)
				bCycle = true;

			if (Visited[Dst] == false)
			{
				Visited[Dst] = true;
				Q.push(Dst);
				++Cnt;
			}
		}
	}
}

void Dijkstra()
{
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

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ get<0>(Edge) };
			auto W{ get<1>(Edge) };
			auto NewDist{ CurDist + W };

			if (NewDist > K)
				continue;

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
	Bfs();

	if (bCycle)
	{
		cout << Cnt << endl;

		for (int i{ 2 }; i <= N; ++i)
		{
			if (Visited[i] == true)
				cout << i << ' ';
		}
	}
	else
	{
		Dijkstra();

		for (int i{ 2 }; i <= N; ++i)
		{
			if (Dist[i] <= K)
				Result.push_back(i);
		}

		cout << Result.size() << endl;

		for (auto& V : Result)
		{
			cout << V << ' ';
		}
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