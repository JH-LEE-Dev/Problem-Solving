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
vector<pair<int, int>> Query;
vector<vector<int>> Lines(100'001, vector<int>(5, -1));
vector<vector<int>> Dist(5 * MAX, vector<int>(5 * MAX, INF));

int GetEdgeID(int Type, int Line)
{
	return M * Type + Line;
}

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < 5; ++j)
		{
			cin >> Lines[i][j];
		}

		for (int j{ 0 }; j < 5; ++j)
		{
			for (int k{ 0 }; k < 5; ++k)
			{
				Dist[GetEdgeID(j, Lines[i][j])][GetEdgeID(k, Lines[i][k])] = 1;
			}
		}
	}

	cin >> Q;

	for (int i{ 0 }; i < Q; ++i)
	{
		int Start, End;
		cin >> Start >> End;

		Query.push_back({ Start,End });
	}
}

void FloydWarshall()
{
	for (int i{ 0 }; i <= 5 * M; ++i)
	{
		Dist[i][i] = 0;
	}

	for (int Middle{ 0 }; Middle <= 5 * M; ++Middle)
	{
		for (int Left{ 0 }; Left <= 5 * M; ++Left)
		{
			for (int Right{ 0 }; Right <= 5 * M; ++Right)
			{
				Dist[Left][Right] = min(Dist[Left][Right], Dist[Left][Middle] + Dist[Middle][Right]);
			}
		}
	}
}

void Solve()
{
	FloydWarshall();

	for (int i{ 0 }; i < Q; ++i)
	{
		auto [Start, End] {Query[i]};

		Start -= 1;
		End -= 1;

		int Result{ INF };

		for (int j{ 0 }; j < 5; ++j)
		{
			for (int k{ 0 }; k < 5; ++k)
			{
				Result = min(Result, Dist[GetEdgeID(j, Lines[Start][j])][GetEdgeID(k, Lines[End][k])]);
			}
		}

		if (Result == INF)
			cout << -1 << endl;
		else
			cout << Result + 1 << endl;
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