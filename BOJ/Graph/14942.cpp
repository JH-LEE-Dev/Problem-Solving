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

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 100'001

int N;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<int> Energies(MAX, 0);
vector<LL> Dist(MAX, INF);
vector<int> Childs(MAX, 0);

void Input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		cin >> Energies[i];
	}

	for (int i{ 0 }; i < N - 1; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });
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
				Childs[Dst] = Src;
			}
		}
	}
}

int Tracking(int Start)
{
	int CurDist{ 0 };
	auto Cursor{ Start };
	auto Ret{ Start };

	while (true)
	{
		if (Dist[Start] - Dist[Cursor] > Energies[Start])
			return Ret;
		else if (Dist[Start] - Dist[Cursor] == Energies[Start])
			return Cursor;

		Ret = Cursor;
		Cursor = Childs[Cursor];
	}
}

void Solve()
{
	Dijkstra();

	for (int i{ 1 }; i <= N; ++i)
	{
		if (Dist[i] <= Energies[i])
			cout << 1 << endl;
		else
			cout << Tracking(i) << endl;
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