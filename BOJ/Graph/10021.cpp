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
using State = tuple<LL, LL>;

#define endl '\n'
#define INF numeric_limits<LL>::max()

int N, C;
vector<pair<LL, LL>> Points;

void Input()
{
	cin >> N >> C;

	for (int i{ 0 }; i < N; ++i)
	{
		int X, Y;
		cin >> X >> Y;

		Points.push_back({ X,Y });
	}
}

void Mst()
{
	vector<LL> Dist(N + 5, INF);
	vector<bool> Visited(N + 5, false);
	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ 0,0 });
	Dist[0] = 0;

	LL MstWeight{ 0 };

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto [CurW, CurId] {Cur};
		auto [X, Y] {Points[CurId]};

		if (Dist[CurId] < CurW)
			continue;

		Visited[CurId] = true;

		for (int i{ 0 }; i < Points.size(); ++i)
		{
			if (i == CurId)
				continue;

			auto [DstX, DstY] {Points[i]};
			auto DeltaX{ X - DstX };
			auto DeltaY{ Y - DstY };
			auto Distance{ DeltaX * DeltaX + DeltaY * DeltaY };

			if (Distance < C)
				continue;

			if (Visited[i] == false)
			{
				if (Dist[i] > Distance)
				{
					Dist[i] = Distance;
					PQ.push({ Distance,i });
				}
			}
		}
	}

	for (int i{ 0 }; i < N; ++i)
	{
		if (Dist[i] == INF)
		{
			cout << -1;
			return;
		}

		MstWeight += Dist[i];
	}

	cout << MstWeight;
}

void Solve()
{
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