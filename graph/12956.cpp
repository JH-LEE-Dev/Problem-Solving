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

#define endl '\n'
#define INF numeric_limits<int>::max()/2
#define MAX 101

int N, M;
vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));
vector<vector<int>> Dist_Origin(MAX, vector<int>(MAX, INF));
vector<vector<int>> Dist_Banned;
vector<tuple<int, int, int>> Edges;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges.push_back({ Src,Dst,W });
		Dist[Src][Dst] = W;
		Dist[Dst][Src] = W;
		Dist_Origin[Src][Dst] = W;
		Dist_Origin[Dst][Src] = W;
	}
}

void FloydWarshall()
{
	for (int i{ 0 }; i < N; ++i)
	{
		Dist[i][i] = 0;
	}

	for (int Middle{ 0 }; Middle < N; ++Middle)
	{
		for (int Left{ 0 }; Left < N; ++Left)
		{
			for (int Right{ 0 }; Right < N; ++Right)
			{
				Dist[Left][Right] = min(Dist[Left][Right], Dist[Left][Middle] + Dist[Middle][Right]);
			}
		}
	}
}

void FloydWarshall_Banned(int Cnt)
{
	for (int i{ 0 }; i < N; ++i)
	{
		Dist_Banned[i][i] = 0;
	}

	auto Banned{ Edges[Cnt] };
	int Banned_Src{ get<0>(Banned) };
	int Banned_Dst{ get<1>(Banned) };

	Dist_Banned[Banned_Src][Banned_Dst] = INF;
	Dist_Banned[Banned_Dst][Banned_Src] = INF;

	for (int Middle{ 0 }; Middle < N; ++Middle)
	{
		for (int Left{ 0 }; Left < N; ++Left)
		{
			for (int Right{ 0 }; Right < N; ++Right)
			{
				Dist_Banned[Left][Right] = min(Dist_Banned[Left][Right], Dist_Banned[Left][Middle] + Dist_Banned[Middle][Right]);
			}
		}
	}
}

void Solve()
{
	FloydWarshall();

	for (int i{ 0 }; i < M; ++i)
	{
		int Cnt{ 0 };

		Dist_Banned = Dist_Origin;

		FloydWarshall_Banned(i);

		for (int j{ 0 }; j < N; ++j)
		{
			for (int k{ j }; k < N; ++k)
			{
				if (j == k)
					continue;

				if (Dist[j][k] < Dist_Banned[j][k])
					++Cnt;
			}
		}

		cout << Cnt << ' ';
	}
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