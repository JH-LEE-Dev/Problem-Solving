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
using Vertex = tuple<LL, int, int, char>;

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 31

//Same,Other
int N, A, B;
vector<vector<char>> Table(MAX, vector<char>(MAX, '.'));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

LL Result{ 0 };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= N || C < 0)
		return false;
	else
		return true;
}

void Input()
{
	cin >> N >> A >> B;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

void Dijkstra(pair<int, int> Start, char Type)
{
	vector<vector<LL>> Dist(MAX, vector<LL>(MAX, INF));

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,Start.first,Start.second,Type });
	Dist[Start.first][Start.second] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto R{ get<1>(Cur) };
		auto C{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurType{ get<3>(Cur) };

		if (Dist[R][C] < CurDist)
			continue;

		Result = max(Result, CurDist);

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ R + Dir_Row[i] };
			auto nC{ C + Dir_Col[i] };

			if (IsValid(nR, nC) == false)
				continue;

			auto NewDist{ CurDist };

			if (Table[nR][nC] != CurType)
			{
				NewDist += B;
			}
			else
			{
				NewDist += A;
			}

			if (Dist[nR][nC] > NewDist)
			{
				Dist[nR][nC] = NewDist;
				PQ.push({ NewDist,nR,nC,Table[nR][nC] });
			}
		}
	}
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			Dijkstra({ i,j }, Table[i][j]);
		}
	}

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