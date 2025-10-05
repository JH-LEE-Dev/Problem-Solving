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
using State = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 2'001

int N, M;
vector<vector<int>> Edges(MAX, vector<int>());

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst;
		cin >> Src >> Dst;

		Edges[Src].push_back(Dst);
		Edges[Dst].push_back(Src);
	}
}

bool Dfs(int CurCnt, int Src, vector<bool>& Visited)
{
	Visited[Src] = true;

	if (CurCnt == 5)
		return true;

	for (const auto& Dst : Edges[Src])
	{
		if (Visited[Dst] == false)
		{
			if (Dfs(CurCnt + 1, Dst, Visited))
				return true;
		}
	}

	Visited[Src] = false;

	return false;
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		vector<bool> Visited(MAX, false);

		if (Dfs(1, i, Visited))
		{
			cout << 1;
			return;
		}
	}

	cout << 0;
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