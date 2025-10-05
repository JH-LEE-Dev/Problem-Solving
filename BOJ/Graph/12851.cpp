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
#define MAX 100'000

int Start, End;
vector<int> Dist(MAX + 5, INF);
vector<int> Cnt(MAX + 5, -1);
vector<vector<int>> Parents(MAX + 5, vector<int>());

void Input()
{
	cin >> Start >> End;
}

void Bfs()
{
	queue<int> Q;
	Q.push(Start);
	Dist[Start] = 0;

	while (Q.empty() == false)
	{
		auto Src{ Q.front() };
		Q.pop();

		if (Src * 2 <= MAX)
		{
			int Jump{ Src * 2 };

			if (Dist[Jump] > Dist[Src] + 1)
			{
				Dist[Jump] = Dist[Src] + 1;
				Q.push(Jump);
				Parents[Jump].push_back(Src);
			}
			else if (Dist[Jump] == Dist[Src] + 1)
			{
				Parents[Jump].push_back(Src);
			}
		}

		if (Src - 1 >= 0)
		{
			int Jump{ Src - 1 };

			if (Dist[Jump] > Dist[Src] + 1)
			{
				Dist[Jump] = Dist[Src] + 1;
				Q.push(Jump);
				Parents[Jump].push_back(Src);
			}
			else if (Dist[Jump] == Dist[Src] + 1)
			{
				Parents[Jump].push_back(Src);
			}
		}

		if (Src + 1 <= MAX)
		{
			int Jump{ Src + 1 };

			if (Dist[Jump] > Dist[Src] + 1)
			{
				Dist[Jump] = Dist[Src] + 1;
				Q.push(Jump);
				Parents[Jump].push_back(Src);
			}
			else if (Dist[Jump] == Dist[Src] + 1)
			{
				Parents[Jump].push_back(Src);
			}
		}
	}
}

int Dfs(int Src)
{
	if (Cnt[Src] != -1)
		return Cnt[Src];

	if (Parents[Src].size() == 0)
		return 1;

	Cnt[Src] = 0;

	for (const auto& Par : Parents[Src])
	{
		Cnt[Src] += Dfs(Par);
	}

	return Cnt[Src];
}

void Solve()
{
	Bfs();

	cout << Dist[End] << endl;

	cout << Dfs(End);
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