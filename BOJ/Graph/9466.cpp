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
#define MAX 100'001

int T, N;
vector<vector<int>> Edges;
vector<bool> Visited;
vector<bool> Check;
vector<int> Parent;
bool bCycle{ false };
int Result;

void Input()
{
	cin >> N;
	Edges = vector<vector<int>>(MAX, vector<int>());
	Visited = vector<bool>(MAX, false);
	Check = vector<bool>(MAX, false);
	Parent = vector<int>(MAX, -1);
	Result = 0;

	for (int i{ 1 }; i <= N; ++i)
	{
		int Dst;
		cin >> Dst;

		Edges[i].push_back(Dst);

		if (i == Dst)
		{
			Visited[i] = true;
			Check[i] = true;
			++Result;
		}
	}
}

void GatherCycle(int Start, int End)
{
	int Cursor{ Start };
	Check[Start] = true;
	++Result;

	while (true)
	{
		if (Cursor == End)
			break;

		Cursor = Parent[Cursor];
		Check[Cursor] = true;
		++Result;
	}
}

bool Dfs(int Src)
{
	Visited[Src] = true;

	bool bValid{ true };

	for (const auto& Dst : Edges[Src])
	{
		if (Visited[Dst] == false)
		{
			Parent[Dst] = Src;
			bValid = Dfs(Dst);
		}
		else if (Check[Dst] == false)
		{
			bCycle = true;

			GatherCycle(Src, Dst);
		}
		else
			bValid = false;
	}

	Check[Src] = true;

	if (bValid == false || bCycle)
		return false;

	++Result;
	return true;
}

void Solve()
{
	cin >> T;

	while (T != 0)
	{
		Input();

		for (int i{ 1 }; i <= N; ++i)
		{
			bCycle = false;

			if (Visited[i] == false)
				Dfs(i);
		}

		cout << N - Result << endl;

		--T;
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