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
#define MAX 201

int N, M;
unordered_map<string, unordered_map<string, int>> Dist;
unordered_set<string> Vertexes;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		string Left;
		string Right;

		for (int j{ 0 }; j < 5; ++j)
		{
			string Str;
			cin >> Str;

			if (j == 0)
				Left = Str;

			if (j == 4)
				Right = Str;
		}

		Vertexes.insert(Left);
		Vertexes.insert(Right);

		Dist[Left][Right] = 1;
	}
}

void FloydWarshall()
{
	for (auto& V : Vertexes)
	{
		Dist[V][V] = 1;
	}

	for (auto& Middle : Vertexes)
	{
		for (auto& Left : Vertexes)
		{
			for (auto& Right : Vertexes)
			{
				if (Dist[Left].find(Right) == Dist[Left].end())
					Dist[Left][Right] = INF;

				if (Dist[Left].find(Middle) == Dist[Left].end())
					Dist[Left][Middle] = INF;

				if (Dist[Middle].find(Right) == Dist[Middle].end())
					Dist[Middle][Right] = INF;

				Dist[Left][Right] = min(Dist[Left][Right], Dist[Left][Middle] + Dist[Middle][Right]);
			}
		}
	}
}

void Solve()
{
	FloydWarshall();

	for (int i{ 0 }; i < M; ++i)
	{
		string Left;
		string Right;

		for (int j{ 0 }; j < 5; ++j)
		{
			string Str;
			cin >> Str;

			if (j == 0)
				Left = Str;

			if (j == 4)
				Right = Str;
		}

		if (Vertexes.find(Left) == Vertexes.end() || Vertexes.find(Right) == Vertexes.end())
		{
			cout << "Pants on Fire" << endl;

			continue;
		}

		if (Dist[Left][Right] != INF)
		{
			cout << "Fact" << endl;

			continue;
		}

		if (Dist[Left][Right] == INF && Dist[Right][Left] != INF)
		{
			cout << "Alternative Fact" << endl;

			continue;
		}

		if (Dist[Left][Right] == INF && Dist[Right][Left] == INF)
		{
			cout << "Pants on Fire" << endl;

			continue;
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