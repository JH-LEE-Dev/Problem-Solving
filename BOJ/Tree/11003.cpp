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
#define MAX 1'000'001

int N, M, K;
vector<LL> Arr;
vector<LL> SegTree;

void Input()
{
	cin >> N >> M >> K;

	SegTree.resize(N * 2);

	for (int i{ 0 }; i < N; ++i)
	{
		LL Temp;
		cin >> Temp;

		Arr.push_back(Temp);
		SegTree[i + N] = Temp;
	}
}

void InitTree()
{
	for (int i{ N - 1 }; i > 0; --i)
		SegTree[i] = SegTree[i << 1] + SegTree[i << 1 | 1];
}

LL Query(int Left, int Right)
{
	LL Ret{ 0 };

	for (Left += N, Right += N; Left < Right; Left >>= 1, Right >>= 1)
	{
		if (Left & 1)
		{
			Ret += SegTree[Left];
			++Left;
		}

		if (Right & 1)
		{
			--Right;
			Ret += SegTree[Right];
		}
	}

	return Ret;
}

void Update(int Idx, LL Val)
{
	for (SegTree[Idx += N] = Val; Idx > 1; Idx >>= 1)
		SegTree[Idx >> 1] = SegTree[Idx] + SegTree[Idx ^ 1];
}

void Solve()
{
	InitTree();

	for (int i{ 0 }; i < M + K; ++i)
	{
		int Type;
		cin >> Type;

		if (Type == 1)
		{
			LL Idx, Val;
			cin >> Idx >> Val;

			Update(Idx - 1, Val);
		}
		else
		{
			LL Start, End;
			cin >> Start >> End;

			cout << Query(Start - 1, End) << endl;
		}
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