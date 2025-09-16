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
#define INF numeric_limits<int>::max()
#define MAX 250'001

int N, Q;
vector<vector<int>> Edges(MAX, vector<int>());
vector<int> VParent(MAX, 0);
vector<vector<int>> Query(100'001, vector<int>());
vector<int> Parent(MAX, 0);
vector<int> Rank(MAX, 1);
vector<LL> Cnt(MAX, 1);
vector<bool> Visited(MAX, false);

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N - 1; ++i)
	{
		int Src, Dst;
		cin >> Src >> Dst;

		Edges[Src].push_back(Dst);
		Edges[Dst].push_back(Src);
	}

	cin >> Q;

	for (int i{ 0 }; i < Q; ++i)
	{
		int Num;
		cin >> Num;

		for (int j{ 0 }; j < Num; ++j)
		{
			int Temp;
			cin >> Temp;

			Query[i].push_back(Temp);
		}
	}
}

void Bfs()
{
	queue<int> Q;
	vector<bool> Visited(MAX, false);
	Visited[1] = 0;
	Q.push({ 1 });
	VParent[1] = 1;

	while (Q.empty() == false)
	{
		auto Src{ Q.front() };
		Q.pop();

		for (auto& Dst : Edges[Src])
		{
			if (Visited[Dst] == false)
			{
				Visited[Dst] = true;
				VParent[Dst] = Src;
				Q.push(Dst);
			}
		}
	}
}

int Find(int U)
{
	if (Parent[U] == U)
		return U;

	return Parent[U] = Find(Parent[U]);
}

void Merge(int U, int V)
{
	int Par_U{ Find(U) };
	int Par_V{ Find(V) };

	if (Par_U == Par_V)
		return;

	if (Rank[Par_U] > Rank[Par_V])
		swap(Par_U, Par_V);

	Parent[Par_U] = Par_V;
	Cnt[Par_V] += Cnt[Par_U];

	if (Rank[Par_U] == Rank[Par_V])
		++Rank[Par_V];
}

void Calc(vector<int>& Arr)
{
	LL Result{ 0 };

	for (const auto& V : Arr)
	{
		Parent[V] = V;
		Visited[V] = true;
	}

	for (const auto& V : Arr)
	{
		if (Visited[VParent[V]])
			Merge(V, VParent[V]);
	}

	for (const auto& V : Arr)
	{
		const auto& Par_V{ Find(V) };

		if (Visited[Par_V])
		{
			if (Cnt[Par_V] > 1)
				Result += Cnt[Par_V] * (Cnt[Par_V] - 1) / 2;

			Visited[Par_V] = false;
		}
	}

	for (const auto& V : Arr)
	{
		Visited[V] = false;
		Rank[V] = 1;
		Cnt[V] = 1;
	}

	cout << Result << endl;
}

void Solve()
{
	Bfs();

	for (int i{ 0 }; i < Q; ++i)
	{
		Calc(Query[i]);
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