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
#define INF numeric_limits<int>::max()
#define MAX 501

int N, M;
vector<vector<int>> D(MAX, vector<int>(MAX, 0));
vector<vector<int>> Dist(MAX, vector<int>(MAX, -INF));

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		vector<int> Rank(N + 1);

		for (int j{ 1 }; j <= N; ++j)
			cin >> Rank[j];

		for (int j{ 1 }; j <= N; ++j)
		{
			for (int k{ 1 }; k <= N; ++k)
			{
				if (j == k)
					continue;

				if (Rank[j] != 0 && Rank[k] == 0)
				{
					++D[j][k];
				}
				else if (Rank[j] != 0 && Rank[k] != 0 && Rank[j] < Rank[k])
				{
					++D[j][k];
				}
			}
		}
	}
}

void FloydWarshall()
{
	for (int i{ 1 }; i <= N; i++)
	{
		for (int j{ 1 }; j <= N; j++)
		{
			if (i == j)
				continue;

			if (D[i][j] > D[j][i])
				Dist[i][j] = D[i][j];
			else
				Dist[i][j] = 0;
		}
	}

	for (int Middle{ 1 }; Middle <= N; ++Middle)
	{
		for (int Left{ 1 }; Left <= N; ++Left)
		{
			for (int Right{ 1 }; Right <= N; ++Right)
			{
				Dist[Left][Right] = max(Dist[Left][Right], min(Dist[Left][Middle], Dist[Middle][Right]));
			}
		}
	}
}

void Solve()
{
	FloydWarshall();

	for (int i{ 1 }; i <= N; ++i)
	{
		bool bValid{ true };

		for (int j{ 1 }; j <= N; ++j)
		{
			if (i == j)
				continue;

			if (Dist[i][j] < Dist[j][i])
			{
				bValid = false;
				break;
			}
		}

		if (bValid)
			cout << i << ' ';
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