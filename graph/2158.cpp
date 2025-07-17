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
using Vertex = tuple<double, double, int, int, int>;

#define endl '\n'
#define INF numeric_limits<double>::max()
#define MAX 101

int V, N, M;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<double>> Dist(MAX, vector<double>(MAX, INF));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

double ResultDist{ 0 };

void Input()
{
	cin >> V >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0)
		return false;
	else
		return true;
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,-V,0,0,0 });
	Dist[0][0] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto R{ get<3>(Cur) };
		auto C{ get<4>(Cur) };
		auto CurSpeed{ -get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurDelta{ get<2>(Cur) };

		if (R == N - 1 && C == M - 1)
		{
			ResultDist = CurDist;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			double NewSpeed{ (double)CurSpeed * pow(2,CurDelta) };
			auto NewDist{ CurDist + (double)1 / NewSpeed };

			auto NewDelta{ Table[R][C] - Table[NewR][NewC] };

			if (Dist[NewR][NewC] > NewDist)
			{
				Dist[NewR][NewC] = NewDist;
				PQ.push({ NewDist,-NewSpeed,NewDelta,NewR,NewC });
			}
		}
	}
}

void Solve()
{
	Dijkstra();

	cout << fixed << setprecision(10) << ResultDist;
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