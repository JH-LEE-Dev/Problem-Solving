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
using State = tuple<LL, LL, LL, LL>;

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 501

int N, M, X;
vector<vector<tuple<LL, LL, LL>>> Edges(MAX, vector<tuple<LL, LL, LL>>());
vector<pair<LL, LL>> MinVal(MAX, pair<LL, LL>(INF, INF));

void Input()
{
	cin >> N >> M >> X;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W1, W2;
		cin >> Src >> Dst >> W1 >> W2;

		Edges[Src].push_back({ Dst,W1,W2 });
		Edges[Dst].push_back({ Src,W1,W2 });
	}
}

void Dijkstra()
{
	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ 0,0,-INF,1 });
	MinVal[1] = { 0,-INF };

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto [CurDist, CurL, CurC, Src] {Cur};

		if (MinVal[Src].first < CurL && MinVal[Src].second < CurC)
			continue;

		if (Src == N)
		{
			cout << CurDist;
			return;
		}

		for (auto& Edge : Edges[Src])
		{
			auto [Dst, L, C] {Edge};
			auto NewL{ CurL + L };
			auto NewC{ min(C,-CurC) };

			if (MinVal[Dst].first > NewL || MinVal[Dst].second > -NewC)
			{
				MinVal[Dst].first = min(MinVal[Dst].first, NewL);
				MinVal[Dst].second = min(MinVal[Dst].second, -NewC);

				PQ.push({ NewL + X / NewC,NewL,-NewC,Dst });
			}
		}
	}
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