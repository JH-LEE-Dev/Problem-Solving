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
using Vertex = tuple<int, int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 51

int N, K;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<pair<int, int>>> NumberCoord(MAX* MAX, vector<pair<int, int>>());
vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));

void Input()
{
	cin >> N >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> Table[i][j];

			NumberCoord[Table[i][j]].push_back({ i,j });
		}
	}
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;

	for (int i{ 0 }; i < NumberCoord[1].size(); ++i)
	{
		PQ.push({ 0,1,NumberCoord[1][i].first,NumberCoord[1][i].second });
		Dist[NumberCoord[1][i].first][NumberCoord[1][i].second] = 0;
	}

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto R{ get<2>(Cur) };
		auto C{ get<3>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurNumber{ get<1>(Cur) };

		if (Dist[R][C] < CurDist)
			continue;

		if (CurNumber == K)
		{
			cout << CurDist;
			return;
		}

		for (int i{ 0 }; i < NumberCoord[CurNumber + 1].size(); ++i)
		{
			auto NewR{ NumberCoord[CurNumber + 1][i].first };
			auto NewC{ NumberCoord[CurNumber + 1][i].second };
			auto W{ abs(R - NewR) + abs(C - NewC) };
			auto NewDist{ CurDist + W };

			if (Dist[NewR][NewC] > NewDist)
			{
				Dist[NewR][NewC] = NewDist;
				PQ.push({ NewDist,CurNumber + 1,NewR,NewC });
			}
		}
	}

	cout << -1;
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