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
using Vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N, M;
vector<vector<int>> Edges(MAX, vector<int>(MAX, INF));
vector<int> Path;
vector<vector<int>> Dist(MAX, vector<int>(10'001, INF));

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Temp;
		cin >> Temp;

		Path.push_back(Temp);
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			cin >> Edges[i][j];
		}
	}
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,1,0 });
	Dist[1][0] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurCnt{ get<2>(Cur) };

		if (Dist[Src][CurCnt] < CurDist)
			continue;

		if (Src == Path[M - 1] && CurCnt == M - 1)
		{
			cout << CurDist;
			return;
		}

		for (int i{ 1 }; i <= N; ++i)
		{
			if (Src == i)
				continue;

			auto NewDist{ CurDist + Edges[Src][i] };

			if (i == Path[CurCnt + 1])
			{
				if (Dist[i][CurCnt + 1] > NewDist)
				{
					Dist[i][CurCnt + 1] = NewDist;
					PQ.push({ NewDist,i,CurCnt + 1 });
				}
			}
			else
			{
				if (Dist[i][CurCnt] > NewDist)
				{
					Dist[i][CurCnt] = NewDist;
					PQ.push({ NewDist,i,CurCnt });
				}
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