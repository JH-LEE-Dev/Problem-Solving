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
using Vertex = tuple<LL, int>;

#define endl '\n'
#define INF numeric_limits<LL>::max()/2
#define MAX 301

int N, M, S, T, Q;
vector<vector<LL>> Dist(MAX, vector<LL>(MAX, INF));

void Input()
{
	cin >> N >> M >> S >> T;

	for (int i{ 0 }; i < M; ++i)
	{
		LL Src, Dst, W;

		cin >> Src >> Dst >> W;

		Dist[Src][Dst] = min(Dist[Src][Dst], W);
	}
}

void FloydWarshall()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		Dist[i][i] = 0;
	}

	for (int Middle{ 1 }; Middle <= N; ++Middle)
	{
		for (int Left{ 1 }; Left <= N; ++Left)
		{
			for (int Right{ 1 }; Right <= N; ++Right)
			{
				Dist[Left][Right] = min(Dist[Left][Right], Dist[Left][Middle] + Dist[Middle][Right]);
			}
		}
	}
}

void Solve()
{
	cin >> Q;

	FloydWarshall();

	for (int i{ 0 }; i < Q; ++i)
	{
		int Src_1, Dst_1, Src_2, Dst_2, W1, W2;

		cin >> Src_1 >> Dst_1 >> W1 >> Src_2 >> Dst_2 >> W2;

		auto Dist1To2{ INF };
		auto Dist2To1{ INF };
		auto Dist1{ INF };
		auto Dist2{ INF };

		if (Dist[S][Src_1] != INF && Dist[Dst_1][Src_2] != INF && Dist[Dst_2][T] != INF)
		{
			Dist1To2 = Dist[S][Src_1] + W1 + Dist[Dst_1][Src_2] + W2 + Dist[Dst_2][T];
		}

		if (Dist[S][Src_2] != INF && Dist[Dst_2][Src_1] != INF && Dist[Dst_1][T] != INF)
		{
			Dist2To1 = Dist[S][Src_2] + W2 + Dist[Dst_2][Src_1] + W1 + Dist[Dst_1][T];
		}

		if (Dist[S][Src_1] != INF && Dist[Dst_1][T] != INF)
		{
			Dist1 = Dist[S][Src_1] + W1 + Dist[Dst_1][T];
		}

		if (Dist[S][Src_2] != INF && Dist[Dst_2][T] != INF)
		{
			Dist2 = Dist[S][Src_2] + W2 + Dist[Dst_2][T];
		}

		auto ResultDist{ min(Dist[S][T],Dist1) };

		ResultDist = min(ResultDist, Dist2);

		ResultDist = min(ResultDist, Dist1To2);
		ResultDist = min(ResultDist, Dist2To1);

		if (ResultDist == INF)
			cout << -1 << endl;
		else
			cout << ResultDist << endl;
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