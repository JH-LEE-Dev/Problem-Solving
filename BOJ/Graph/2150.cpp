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
#define MAX 10'001

int N, M;
vector<vector<int>> Edges(MAX, vector<int>());
vector<vector<int>> ReverseEdges(MAX, vector<int>());
vector<bool> Visited(MAX, false);
stack<int> MyStack;
vector<vector<int>> SCC;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst;

		cin >> Src >> Dst;

		Edges[Src].push_back(Dst);
		ReverseEdges[Dst].push_back(Src);
	}
}

void Dfs(int Src)
{
	Visited[Src] = true;

	for (const auto& Dst : Edges[Src])
	{
		if (Visited[Dst] == false)
		{
			Dfs(Dst);
		}
	}

	MyStack.push(Src);
}

void CollectSCC(int Src, vector<int>& Arr)
{
	Arr.push_back(Src);
	Visited[Src] = true;

	for (const auto& Dst : ReverseEdges[Src])
	{
		if (Visited[Dst] == false)
		{
			CollectSCC(Dst, Arr);
		}
	}
}

void Solve()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		if (Visited[i] == false)
			Dfs(i);
	}

	fill(Visited.begin(), Visited.end(), false);

	while (MyStack.empty() == false)
	{
		auto Cur{ MyStack.top() };
		MyStack.pop();

		if (Visited[Cur] == true)
			continue;

		vector<int> CurSCC;

		CollectSCC(Cur, CurSCC);

		sort(CurSCC.begin(), CurSCC.end());
		CurSCC.push_back(-1);
		SCC.push_back(CurSCC);
	}

	sort(SCC.begin(), SCC.end());

	cout << SCC.size() << endl;

	for (const auto& CurSCC : SCC)
	{
		for (const auto& V : CurSCC)
		{
			cout << V << ' ';
		}

		cout << endl;
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