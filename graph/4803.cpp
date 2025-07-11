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
vector<vector<int>> Edges;
bool IsValid{ true };
vector<bool> Visited;

void Input()
{
	Edges = vector<vector<int>>(MAX, vector<int>());
	Visited = vector<bool>(MAX, false);

	cin >> N >> M;

	if (N == 0 && M == 0)
	{
		IsValid = false;
		return;
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst;

		cin >> Src >> Dst;

		Edges[Src].push_back(Dst);
		Edges[Dst].push_back(Src);
	}
}

bool Dfs(int Parent, int Cur)
{
	Visited[Cur] = true;

	for (auto& Dst : Edges[Cur])
	{
		if (Dst == Parent)
			continue;

		if (Visited[Dst] == false)
		{
			Visited[Dst] = true;

			if (Dfs(Cur, Dst) == false)
				return false;
		}
		else if (Dst != Parent)
		{
			return false;
		}
	}

	return true;
}

void Solve()
{
	int Cnt{ 1 };

	while (true)
	{
		IsValid = true;
		Input();

		int Result{ 0 };

		if (IsValid == false)
			return;

		for (int i{ 1 }; i <= N; ++i)
		{
			if (Visited[i] == false)
			{
				if (Dfs(i, i))
					++Result;
			}
		}

		if (Result > 1)
		{
			cout << "Case " << Cnt << ": A forest of " << Result << " trees." << endl;
		}

		if (Result == 1)
		{
			cout << "Case " << Cnt << ": There is one tree. " << endl;
		}

		if (Result == 0)
		{
			cout << "Case " << Cnt << ": No trees." << endl;
		}

		++Cnt;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}