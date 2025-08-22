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
#define INF numeric_limits<LL>::max()
#define MAX 100'001

int N;
vector<int> Arr(MAX, 0);
vector<LL> SegTree;
bool IsEnd{ false };

void Input()
{
	SegTree.clear();
	cin >> N;

	if (N == 0)
	{
		IsEnd = true;
		return;
	}

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	SegTree.resize(TreeSize);

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> Arr[i];
	}
}

int InitTree(int Node, int Start, int End)
{
	if (Start == End)
	{
		SegTree[Node] = Start;

		return Start;
	}

	int Middle{ (Start + End) / 2 };

	auto Left{ InitTree(Node * 2,Start,Middle) };
	auto Right{ (InitTree(Node * 2 + 1,Middle + 1,End)) };

	if (Arr[Left] < Arr[Right])
	{
		SegTree[Node] = Left;
		return Left;
	}
	else
	{
		SegTree[Node] = Right;
		return Right;
	}
}

LL Query(int Node, int Start, int End, int Left, int Right)
{
	if (Start > Right || End < Left)
		return -1;

	if (Start >= Left && End <= Right)
		return SegTree[Node];

	int Middle{ (Start + End) / 2 };
	LL L{ Query(Node * 2,Start,Middle,Left,Right) };
	LL R{ Query(Node * 2 + 1,Middle + 1,End,Left,Right) };

	if (L == -1)
		return R;

	if (R == -1)
		return L;

	if (Arr[L] < Arr[R])
		return L;
	else
		return R;
}

LL Query_Sum(int Start, int End)
{
	LL MinIdx{ Query(1,0,N - 1,Start,End) };
	LL Result{ (LL)Arr[MinIdx] * ((End + 1) - Start) };

	if (MinIdx >= Start + 1)
	{
		LL Left{ Query_Sum(Start,MinIdx - 1) };

		Result = max(Result, Left);
	}

	if (MinIdx <= End - 1)
	{
		LL Right{ Query_Sum(MinIdx + 1,End) };

		Result = max(Result, Right);
	}

	return Result;
}

void Solve()
{
	while (true)
	{
		Input();

		if (IsEnd)
			return;

		InitTree(1, 0, N - 1);

		cout << Query_Sum(0, N - 1) << endl;
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