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

int N, M, Money;
vector<int> Parent(MAX, 0);
vector<int> Rank(MAX, 1);
vector<bool> Visited(MAX, false);
bool IsValid{ true };

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
	{
		Parent[Par_U] = 0;

		return;
	}

	if (Par_U < Par_V)
		swap(Par_U, Par_V);

	Parent[Par_U] = Par_V;

	//if (Rank[Par_U] < Rank[Par_V])
	//	swap(Par_U, Par_V);

	//Parent[Par_U] = Par_V;

	//if (Rank[Par_U] == Rank[Par_V])
	//	++Rank[Par_V];
}

void Input()
{
	cin >> N >> M;

	if (N == 0 && M == 0)
	{
		IsValid = false;
		return;
	}

	Visited = vector<bool>(MAX, false);

	for (int i{ 1 }; i <= N; ++i)
	{
		Parent[i] = i;
		Rank[i] = 1;
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
	int T{ 0 };

	while (true)
	{
		++T;

		Input();

		if (IsValid == false)
			return;

		int Cnt{ 0 };

		for (int i{ 1 }; i <= N; ++i)
		{
			int Par{ Find(i) };

			if (Visited[Par] == false && Par != 0)
			{
				Visited[Par] = true;
				++Cnt;
			}
		}

		if (Cnt > 1)
		{
			cout << "Case " << T << ": A forest of " << Cnt << " trees." << endl;
		}

		if (Cnt == 1)
		{
			cout << "Case " << T << ": There is one tree. " << endl;
		}

		if (Cnt == 0)
		{
			cout << "Case " << T << ": No trees." << endl;
		}
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