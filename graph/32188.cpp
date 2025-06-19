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
using Vertex = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 100'001

int N, C;
vector<vector<pair<int, int>>> Edges(MAX, vector<pair<int, int>>());
vector<int> Dist(MAX, INF);

void Input()
{
	cin >> N >> C;

	for (int i{ 0 }; i < C; ++i)
	{
		int Type, Start, End;

		cin >> Type >> Start >> End;

		Edges[Start].push_back({ End,Type });
	}
}

void Bfs()
{
	deque<Vertex> DQ;
	DQ.push_front({ 0,0 });
	Dist[0] = 0;

	while (DQ.empty() == false)
	{
		auto Cur{ DQ.front() };
		DQ.pop_front();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src] < CurDist)
			continue;

		if (Src == N - 1)
			return;

		if (Edges[Src].empty() == false)
		{
			auto Dst{ Edges[Src][0].first };
			auto Type{ Edges[Src][0].second };

			if (Type == 0)
			{
				if (Dst != Src)
				{
					if (Dist[Dst] > CurDist)
					{
						Dist[Dst] = CurDist;
						DQ.push_front({ CurDist,Dst });
					}
				}
				else
				{
					if (Dist[Dst] > CurDist)
					{
						Dist[Dst] = CurDist;
						DQ.push_back({ CurDist,Dst });
					}
				}
			}
			else
			{
				if (Dist[Dst] > CurDist)
				{
					Dist[Dst] = CurDist;
					DQ.push_front({ CurDist,Dst });
				}

				if (Dist[Src + 1] > CurDist + 1)
				{
					Dist[Src + 1] = CurDist + 1;
					DQ.push_back({ CurDist + 1,Src + 1 });
				}
			}
		}
		else
		{
			if (Dist[Src + 1] > CurDist + 1)
			{
				Dist[Src + 1] = CurDist + 1;
				DQ.push_back({ CurDist + 1,Src + 1 });
			}
		}
	}
}

void Solve()
{
	Bfs();

	if (Dist[N - 1] == INF)
		cout << -1;
	else
		cout << Dist[N - 1];
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