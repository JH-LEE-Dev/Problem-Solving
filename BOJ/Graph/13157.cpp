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
using State = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N;
int M, T;
vector<vector<tuple<int, int>>> Edges(MAX, vector<tuple<int, int>>());
map<int, set<int>> PrevVertexes;
map<int, int> Cost;

void Input()
{
	cin >> N;

	int Cnt{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> M >> T;

		for (int j{ 0 }; j < M; ++j)
		{
			int S, X;
			cin >> S;
			cin >> X;

			for (int k{ 0 }; k < S; ++k)
			{
				int V;
				cin >> V;

				PrevVertexes[Cnt].insert(V - 1);
			}

			Edges[i].push_back({ Cnt,X - 1 });
			++Cnt;
		}

		Cost[i] = T;
	}
}

void Dijkstra()
{
	vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));
	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ Cost[0],0,0 });
	Dist[0][0] = Cost[0];

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto [CurDist, PrevV, Src] {Cur};

		if (Src == N - 1)
		{
			cout << CurDist;
			return;
		}

		for (const auto& Edge : Edges[Src])
		{
			auto [Id, Dst] {Edge};

			if (PrevVertexes[Id].find(PrevV) != PrevVertexes[Id].end())
				continue;

			auto NewDist{ CurDist + Cost[Dst] };

			if (Dist[Dst][Src] > NewDist)
			{
				Dist[Dst][Src] = NewDist;
				PQ.push({ NewDist,Src,Dst });
			}
		}
	}

	cout << "impossible";
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