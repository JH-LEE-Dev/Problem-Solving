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
#define MAX 501

int N, M, C, T;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<int> Cows;
vector<int> Dist(MAX, INF);

void Input()
{
	cin >> N >> M >> C >> T;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;
		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });
	}

	for (int i{ 0 }; i < C; ++i)
	{
		int Temp;
		cin >> Temp;

		Cows.push_back(Temp);
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

	vector<int> Result;
	for (int i{ 0 }; i < C; ++i)
	{
		if (Dist[Cows[i]] <= T)
			Result.push_back(i + 1);
	}

	sort(Result.begin(), Result.end());

	cout << Result.size() << endl;
	for (const auto& Cow : Result)
	{
		cout << Cow << endl;
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