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
#define MAX 100'001

int N, M;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<int> Dist(MAX, INF);
vector<bool> Visited(MAX, false);
int Result;
int Total;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;
		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });
	}
}

void Prim()
{
	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ 0,1 });
	Dist[1] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto [CurW, Src] {Cur};

		if (Dist[Src] < CurW)
			continue;

		Visited[Src] = true;
		Result = max(CurW, Result);
		Total += CurW;

		for (const auto& Edge : Edges[Src])
		{
			auto [Dst, W] {Edge};

			if (Visited[Dst] == false)
			{
				if (Dist[Dst] > W)
				{
					Dist[Dst] = W;
					PQ.push({ W,Dst });
				}
			}
		}
	}

	cout << Total - Result;
}

void Solve()
{
	Prim();
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