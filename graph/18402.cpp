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

int N, E, T, M;
vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));

void Input()
{
	cin >> N >> E >> T >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Dist[Src][Dst] = W;
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
	FloydWarshall();

	int Result{ 0 };

	for (int i{ 1 }; i <= N; ++i)
	{
		if (Dist[i][E] <= T)
			++Result;
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