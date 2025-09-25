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
using State = tuple<LL, int>;
using Coord = tuple<LL, LL, LL>;

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 100'001

int N;
vector<pair<LL, int>> XCoords;
vector<pair<LL, int>> YCoords;
vector<pair<LL, int>> ZCoords;
vector<vector<pair<int, LL>>> Edges(MAX, vector<pair<int, LL>>());

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		LL X, Y, Z;

		cin >> X >> Y >> Z;

		XCoords.push_back({ X,i });
		YCoords.push_back({ Y,i });
		ZCoords.push_back({ Z,i });
	}
}

void GenerateGraph()
{
	sort(XCoords.begin(), XCoords.end());
	sort(YCoords.begin(), YCoords.end());
	sort(ZCoords.begin(), ZCoords.end());

	for (int i{ 0 }; i < N - 1; ++i)
	{
		auto Src{ XCoords[i].second };
		auto Dst{ XCoords[i + 1].second };
		auto W{ abs(XCoords[i].first - XCoords[i + 1].first) };
		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });

		Src = YCoords[i].second;
		Dst = YCoords[i + 1].second;
		W = abs(YCoords[i].first - YCoords[i + 1].first);
		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });

		Src = ZCoords[i].second;
		Dst = ZCoords[i + 1].second;
		W = abs(ZCoords[i].first - ZCoords[i + 1].first);
		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });
	}
}

void Mst()
{
	vector<bool> Visited(MAX, false);
	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ 0,0 });
	vector<LL> Dist(MAX, INF);
	Visited[0] = true;

	LL Result{ 0 };

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto [CurW, Src] {Cur};

		if (Dist[Src] < CurW)
			continue;

		Visited[Src] = true;
		Result += CurW;

		for (const auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };

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

	cout << Result;
}

void Solve()
{
	GenerateGraph();
	Mst();
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