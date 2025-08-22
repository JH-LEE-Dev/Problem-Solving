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

#define endl '\n'
#define INF numeric_limits<LL>::max()/2
#define MAX 301

int N;
vector<vector<LL>> Dist(MAX, vector<LL>(MAX, INF));
vector<vector<LL>> Dist_Result(MAX, vector<LL>(MAX, INF));

void Input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			cin >> Dist[i][j];
			Dist_Result[i][j] = Dist[i][j];
		}
	}
}

void FloydWarshall()
{
	for (int Middle{ 1 }; Middle <= N; ++Middle)
	{
		for (int Left{ 1 }; Left <= N; ++Left)
		{
			for (int Right{ 1 }; Right <= N; ++Right)
			{
				if (Left == Right || Left == Middle || Right == Middle)
					continue;

				if (Dist[Left][Right] > Dist[Left][Middle] + Dist[Middle][Right])
				{
					cout << -1;
					return;
				}

				if (Dist[Left][Right] == Dist[Left][Middle] + Dist[Middle][Right])
				{
					Dist_Result[Left][Right] = INF;
				}
			}
		}
	}

	int Cnt{ 0 };

	vector<tuple<int, int, int>> Edges;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ i }; j <= N; ++j)
		{
			if (i == j)
				continue;

			if (Dist_Result[i][j] != INF)
			{
				Edges.push_back({ i,j,Dist_Result[i][j] });
				++Cnt;
			}
		}
	}

	cout << Cnt << endl;

	for (const auto& Edge : Edges)
	{
		int Src{ get<0>(Edge) };
		int Dst{ get<1>(Edge) };
		int W{ get<2>(Edge) };

		cout << Src << ' ' << Dst << ' ' << W << endl;
	}
}

void Solve()
{
	FloydWarshall();
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