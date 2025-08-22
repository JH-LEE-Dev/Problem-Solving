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

int N, M, Q;
vector<vector<vector<int>>> Dist(MAX, vector<vector<int>>(MAX, vector<int>(MAX, INF)));

void Input()
{
	cin >> N >> M >> Q;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		for (int i{ 1 }; i <= N; ++i)
		{
			Dist[Src][Dst][i] = W;
		}
	}
}

void FloydWarshall(int Target)
{
	for (int i{ 1 }; i <= N; ++i)
	{
		Dist[i][i][Target] = 0;
	}

	for (int Middle{ 1 }; Middle <= N; ++Middle)
	{
		if (Middle == Target)
			continue;

		for (int Left{ 1 }; Left <= N; ++Left)
		{
			for (int Right{ 1 }; Right <= N; ++Right)
			{
				Dist[Left][Right][Target] = min(Dist[Left][Right][Target], Dist[Left][Middle][Target] + Dist[Middle][Right][Target]);
			}
		}
	}
}

void Solve()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		FloydWarshall(i);
	}

	for (int i{ 0 }; i < Q; ++i)
	{
		int Src, Target, Dst;

		cin >> Src >> Target >> Dst;

		if (Dist[Src][Dst][Target] == INF)
			cout << "No" << endl;
		else
			cout << Dist[Src][Dst][Target] << endl;
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