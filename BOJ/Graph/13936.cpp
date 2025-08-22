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

int N, M, K;
vector<vector<int>> Edges(MAX, vector<int>());
vector<vector<int>> Edges_Reverse(MAX, vector<int>());
vector<int> Dist(MAX, INF);
vector<int> Dist_M(MAX, INF);
vector<int> Dist_K(MAX, INF);

vector<int> MArray;
vector<int> KArray;

void Input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < M; ++i)
	{
		int Temp;
		cin >> Temp;

		MArray.push_back(Temp);
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int Temp;
		cin >> Temp;

		KArray.push_back(Temp);
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		int Cnt;
		cin >> Cnt;

		for (int j{ 0 }; j < Cnt; ++j)
		{
			int Dst;
			cin >> Dst;

			Edges[i].push_back(Dst);
			Edges_Reverse[Dst].push_back(i);
		}
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

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		for (auto& Dst : Edges[Src])
		{
			auto NewDist{ CurDist + 1 };

			if (Dist[Dst] == INF)
			{
				Dist[Dst] = NewDist;
				Q.push({ NewDist,Dst });
			}
		}
	}
}


void Bfs_M()
{
	queue<Vertex> Q;

	for (int i{ 0 }; i < M; ++i)
	{
		Dist_M[MArray[i]] = 0;
		Q.push({ 0,MArray[i] });
	}

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		for (auto& Dst : Edges_Reverse[Src])
		{
			auto NewDist{ CurDist + 1 };

			if (Dist_M[Dst] == INF)
			{
				Dist_M[Dst] = NewDist;
				Q.push({ NewDist,Dst });
			}
		}
	}
}

void Bfs_K()
{
	queue<Vertex> Q;

	for (int i{ 0 }; i < K; ++i)
	{
		Dist_K[KArray[i]] = 0;
		Q.push({ 0,KArray[i] });
	}

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		for (auto& Dst : Edges_Reverse[Src])
		{
			auto NewDist{ CurDist + 1 };

			if (Dist_K[Dst] == INF)
			{
				Dist_K[Dst] = NewDist;
				Q.push({ NewDist,Dst });
			}
		}
	}
}

void Solve()
{
	Bfs();
	Bfs_M();
	Bfs_K();

	int Result{ INF };

	for (int i{ 1 }; i <= N; ++i)
	{
		if (Dist[i] == INF || Dist_M[i] == INF || Dist_K[i] == INF)
			continue;

		Result = min(Result, Dist[i] + Dist_M[i] + Dist_K[i]);
	}

	if (Result == INF)
		cout << "impossible";
	else
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