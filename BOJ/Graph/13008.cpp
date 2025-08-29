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
using State = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 51

int N, M, C;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<vector<int>> Dist(MAX, vector<int>(1'001, INF));
int Result{ INF };
priority_queue<State, vector<State>, greater<State>> PQ;

void Input()
{
	cin >> N >> M >> C;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
	}
}

void Dijkstra(int Limit)
{
	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurCnt{ get<1>(Cur) };

		if (Dist[Src][CurCnt] < CurDist)
			continue;

		if (Src == N)
		{
			Result = min(Result, CurDist);
		}

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };

			if (Dist[Dst][CurCnt] > NewDist)
			{
				Dist[Dst][CurCnt] = NewDist;
				PQ.push({ NewDist,CurCnt,Dst });
			}

			if (CurCnt < C)
			{
				NewDist = CurDist - W;
				auto NewCnt{ CurCnt + 1 };

				if (Dist[Dst][NewCnt] > NewDist)
				{
					Dist[Dst][NewCnt] = NewDist;
				}
			}
		}
	}
}

void Solve()
{
	Dist[1][0] = 0;

	for (int i{ 0 }; i <= C; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			if (Dist[j][i] != INF)
				PQ.push({ Dist[j][i],i,j });
		}

		Dijkstra(i);
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