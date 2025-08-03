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
using Vertex = tuple<LL, LL>;

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 200'001

LL N, M;
vector<vector<LL>> Edges(MAX, vector<LL>());
vector<LL> Dist(MAX, INF);
set<LL> Paths;
vector<LL> Path_DP(MAX, -1);
vector<LL> DistCnt(MAX, 0);

void Input()
{
	cin >> N >> M;

	for (LL i{ 0 }; i < M; ++i)
	{
		LL Src, Dst;

		cin >> Src >> Dst;

		Edges[Src].push_back(Dst);
		Edges[Dst].push_back(Src);
	}
}

void Bfs()
{
	queue<Vertex> Q;
	Q.push({ 0,1 });
	Dist[1] = 0;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto CurDist{ get<0>(Cur) };
		auto Src{ get<1>(Cur) };

		for (auto& Dst : Edges[Src])
		{
			if (Dist[Dst] == INF)
			{
				Dist[Dst] = CurDist + 1;
				Q.push({ CurDist + 1,Dst });
			}
		}
	}
}

LL Dfs(LL Src, LL CurDist)
{
	if (Src != N && Src != 1)
	{
		Paths.insert(Src);
	}

	if (Src == 1)
	{
		return 1;
	}

	if (Path_DP[Src] != -1)
		return Path_DP[Src];

	LL Cnt{ 0 };

	for (auto& Dst : Edges[Src])
	{
		if (Dist[Src] == Dist[Dst] + 1)
			Cnt += Dfs(Dst, Dist[Dst]);
	}

	return Path_DP[Src] = Cnt;
}

void Solve()
{
	Bfs();
	Dfs(N, Dist[N]);

	for (auto& V : Paths)
	{
		++DistCnt[Dist[V]];
	}

	for (int i{ 1 }; i <= Paths.size(); ++i)
	{
		if (DistCnt[i] == 1)
		{
			for (auto& V : Paths)
			{
				if (Dist[V] == i)
				{
					cout << V;
					return;
				}
			}
		}
	}

	cout << 1;
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