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
#define MAX 100'001

int N, M, S, E;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<vector<int>> Dist(MAX, vector<int>(2, INF));

int Result{ 0 };

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });
	}

	cin >> S >> E;
}

void Bfs()
{
	deque<Vertex> DQ;
	DQ.push_front({ 0,S,-1 });
	Dist[S][0] = 0;
	Dist[S][1] = 0;

	while (DQ.empty() == false)
	{
		auto Cur{ DQ.front() };
		DQ.pop_front();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurType{ get<2>(Cur) };

		if (Src == E)
		{
			Result = CurDist;
			return;
		}

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto Type{ Edge.second };

			if (CurType == -1)
			{
				Dist[Dst][Type] = CurDist;
				DQ.push_front({ CurDist,Dst,Type });

				continue;
			}

			if (CurType != Type)
			{
				if (Dist[Dst][Type] > CurDist + 1)
				{
					Dist[Dst][Type] = CurDist + 1;
					DQ.push_back({ CurDist + 1,Dst,Type });
				}
			}
			else
			{
				if (Dist[Dst][Type] > CurDist)
				{
					Dist[Dst][Type] = CurDist;
					DQ.push_front({ CurDist,Dst,Type });
				}
			}
		}
	}
}

void Solve()
{
	Bfs();

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