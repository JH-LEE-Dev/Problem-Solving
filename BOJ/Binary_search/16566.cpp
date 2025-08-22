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
#define MAX 4'000'001

int N, M, K;
vector<int> Card_A;
vector<int> Card_B;
vector<int> Parent(MAX, -1);

void Input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < M; ++i)
	{
		int temp;
		cin >> temp;
		Card_B.push_back(temp);
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int temp;
		cin >> temp;
		Card_A.push_back(temp);
	}
}

int Find(int u)
{
	if (Parent[u] == u)
		return u;

	return Parent[u] = Find(Parent[u]);
}

void Union(int u, int v)
{
	int Par_u{ Find(u) };
	int Par_v{ Find(v) };

	if (Par_u == Par_v)
		return;

	Parent[Par_u] = Par_v;
}

int Upper_Bound(int Target)
{
	int Left{ 0 };
	int Right{ M - 1 };

	while (Left <= Right)
	{
		int Middle{ (Left + Right) / 2 };
		int MiddleNum{ Find(Card_B[Middle]) };

		if (MiddleNum <= Target)
			Left = Middle + 1;
		else
			Right = Middle - 1;
	}

	return Left;
}

void Solve()
{
	sort(Card_B.begin(), Card_B.end());

	for (int i{ 0 }; i <= N; ++i)
	{
		Parent[i] = i;
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int Card{ Card_A[i] };

		int Idx{ Upper_Bound(Card) };

		cout << Find(Card_B[Idx]) << endl;

		Union(Card_B[Idx], Idx == 0 ? 0 : Card_B[Idx - 1]);
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