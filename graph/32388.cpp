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
#define MAX 2'005

int N;
pair<int, int> End;
vector<pair<int, int>> Spots;
vector<double> Dist(MAX, INF);

void Input()
{
	cin >> End.first >> End.second;
	cin >> N;

	Spots.push_back({ 0,0 });
	for (int i{ 0 }; i < N; ++i)
	{
		int R, C;
		cin >> R >> C;

		Spots.push_back({ R,C });
	}

	Spots.push_back(End);
}

double Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,0 });
	Dist[0] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto R{ Spots[Src].first };
		auto C{ Spots[Src].second };

		if (Dist[Src] < CurDist)
			continue;

		if (Src == N + 1)
		{
			return CurDist;
		}

		for (int i{ 0 }; i < N + 2; ++i)
		{
			auto NewR{ Spots[i].first };
			auto NewC{ Spots[i].second };
			auto Distance{ hypot(abs(R - NewR),abs(C - NewC)) };

			if (Src != 0)
				Distance -= 1;

			if (i != N + 1)
				Distance -= 1;

			double W{ 0 };

			if (Distance > 0)
			{
				W = Distance;
			}

			auto NewDist{ CurDist + W };

			if (Dist[i] > NewDist)
			{
				Dist[i] = NewDist;
				PQ.push({ NewDist,i });
			}
		}
	}
}

void Solve()
{
	cout << fixed << setprecision(10) << Dijkstra();
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