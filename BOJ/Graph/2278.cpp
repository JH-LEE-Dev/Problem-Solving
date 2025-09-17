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
bool bValid{ true };
int Cnt;

void Input()
{
	cin >> N >> M;

	for (int i{ 1 }; i <= N; ++i)
	{
		Dist[i][i] = 0;

		for (int j{ i + 1 }; j <= N; ++j)
		{
			int Temp;
			cin >> Temp;

			Dist[i][j] = Temp;
			Dist[j][i] = Temp;
		}
	}

	Cnt = N * (N - 1) / 2;
}

void FloydWarshall()
{
	for (int Middle{ 1 }; Middle <= N; ++Middle)
	{
		for (int Left{ 1 }; Left <= N; ++Left)
		{
			for (int Right{ 1 }; Right <= N; ++Right)
			{
				if (Dist[Left][Right] == INF || Dist[Left][Middle] == INF || Dist[Middle][Right] == INF)
					continue;

				if (Left == Right || Left == Middle || Middle == Right)
					continue;

				if (Dist[Left][Right] > Dist[Left][Middle] + Dist[Middle][Right])
				{
					bValid = false;
					return;
				}

				if (Dist[Left][Right] == Dist[Left][Middle] + Dist[Middle][Right])
				{
					--Cnt;
					Dist[Left][Right] = INF;
					Dist[Right][Left] = INF;
				}
			}
		}
	}
}

void Solve()
{
	FloydWarshall();

	if (bValid == false || Cnt > M)
	{
		cout << 0;
		return;
	}
	else
	{
		cout << 1 << endl;
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ i + 1 }; j <= N; ++j)
		{
			if (Dist[i][j] != INF)
				cout << i << ' ' << j << ' ' << Dist[i][j] << endl;
		}
	}

	while (Cnt < M)
	{
		bool bValid{ false };

		for (int i{ 1 }; i <= N; ++i)
		{
			for (int j{ i + 1 }; j <= N; ++j)
			{
				if (Dist[i][j] == INF)
				{
					cout << i << " " << j << " " << 500 << endl;
					Dist[i][j] = 500;
					++Cnt;
					bValid = 1;
				}

				if (bValid)
					break;
			}

			if (bValid)
				break;
		}
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