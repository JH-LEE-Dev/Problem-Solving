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

int N, M;
vector<bool> Visited(MAX, false);
vector<vector<int>> Edges(MAX, vector<int>());
set<int> Apt;
set<int> Candidates;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N - 1; ++i)
	{
		int Src, Dst, W;
		cin >> Src >> Dst >> W;

		Edges[Src].push_back(Dst);
		Edges[Dst].push_back(Src);
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int Temp;
		cin >> Temp;
		Apt.insert(Temp);
		Candidates.insert(Temp);
	}
}

bool Dfs(int V)
{
	Visited[V] = true;

	bool bValid{ false };

	if (Apt.find(V) != Apt.end())
		bValid = true;

	for (auto& Dst : Edges[V])
	{
		if (Visited[Dst] == false)
		{
			if (Dfs(Dst))
				bValid = true;
		}
	}

	if (bValid)
		Candidates.insert(V);

	return bValid;
}

void Solve()
{
	for (auto& V : Apt)
	{
		Dfs(V);
	}

	cout << Candidates.size();
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