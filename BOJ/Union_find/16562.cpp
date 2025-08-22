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

int N, M, Money;
vector<vector<int>> Unions(MAX, vector<int>());
vector<int> Cost(MAX, 0);
vector<int> Parent(MAX, 0);
vector<bool> Visited(MAX, false);

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

	if (Cost[Par_U] < Cost[Par_V])
		swap(Par_U, Par_V);

	Parent[Par_U] = Par_V;
}

void Input()
{
	cin >> N >> M >> Money;

	for (int i{ 1 }; i <= N; ++i)
	{
		cin >> Cost[i];
		Parent[i] = i;
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst;
		cin >> Src >> Dst;

		Merge(Src, Dst);
	}
}

void Solve()
{
	int Result{ 0 };

	for (int i{ 1 }; i <= N; ++i)
	{
		if (Visited[Find(i)] == false)
		{
			Result += Cost[Find(i)];
			Visited[Find(i)] = true;
		}
	}

	if (Result > Money)
		cout << "Oh no";
	else
		cout << Result;
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