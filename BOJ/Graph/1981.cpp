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
using Vertex = tuple<int, int, int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N;

vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<vector<int>>> Dist(MAX, vector<vector<int>>(MAX, vector<int>(201, INF)));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

int Result{ INF };

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= N || C < 0)
		return false;
	else
		return true;
}

bool Dijkstra(int Diff)
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,Table[0][0],Table[0][0],0,0 });
	Dist[0][0][Table[0][0]] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto CurDist{ get<0>(Cur) };
		auto CurMin{ get<1>(Cur) };
		auto CurMax{ get<2>(Cur) };
		auto R{ get<3>(Cur) };
		auto C{ get<4>(Cur) };

		if (Dist[R][C][CurMax] < CurDist)
			continue;

		if (R == N - 1 && C == N - 1)
		{
			Result = CurDist;
			return true;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			auto NewMax{ max(CurMax,Table[NewR][NewC]) };
			auto NewMin{ min(CurMin,Table[NewR][NewC]) };

			auto NewDist{ NewMax - NewMin };

			if (NewDist > Diff)
				continue;

			if (Dist[NewR][NewC][NewMax] > NewDist)
			{
				Dist[NewR][NewC][NewMax] = NewDist;
				PQ.push({ NewDist,NewMin,NewMax,NewR,NewC });
			}
		}
	}

	return false;
}

void Bsearch()
{
	int Left{ 0 };
	int Right{ 200 };

	while (Left <= Right)
	{
		Dist = vector<vector<vector<int>>>(MAX, vector<vector<int>>(MAX, vector<int>(201, INF)));

		int Middle{ (Left + Right) / 2 };

		if (Dijkstra(Middle) == false)
		{
			Left = Middle + 1;
		}
		else
		{
			Right = Middle - 1;
		}
	}
}

void Solve()
{
	Bsearch();

	cout << Result;
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