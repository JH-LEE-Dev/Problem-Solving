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
#define MAX 100'001

int N, Q;
vector<int> Arr;
vector<LL> SegTree;

void Input()
{
	cin >> N >> Q;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back(Temp);
	}
}

LL InitTree(int Node, int Start, int End)
{
	if (Start == End)
		return SegTree[Node] = Arr[Start];

	int Middle{ (Start + End) / 2 };

	InitTree(Node * 2, Start, Middle);
	InitTree(Node * 2 + 1, Middle + 1, End);

	return SegTree[Node] = SegTree[Node * 2] + SegTree[Node * 2 + 1];
}

LL Query(int Node, int Start, int End, int Idx)
{
	if (Start == End)
		return SegTree[Node];

	int Middle{ (Start + End) / 2 };

	if (Middle >= Idx)
		return Query(Node * 2, Start, Middle, Idx);
	else
		return Query(Node * 2 + 1, Middle + 1, End, Idx);
}

void Change(int Node, int Start, int End, int Idx, LL Diff)
{
	if (Start == End)
	{
		SegTree[Node] += Diff;
		return;
	}

	int Middle{ (Start + End) / 2 };

	if (Middle >= Idx)
		Change(Node * 2, Start, Middle, Idx, Diff);
	else
		Change(Node * 2 + 1, Middle + 1, End, Idx, Diff);

	SegTree[Node] = SegTree[Node * 2] + SegTree[Node * 2 + 1];
}

LL Query_Sum(int Node, int Start, int End, int Left, int Right)
{
	if (Start > Right || End < Left)
		return 0;

	if (Start >= Left && End <= Right)
		return SegTree[Node];

	int Middle{ (Start + End) / 2 };

	auto LSum{ Query_Sum(Node * 2,Start,Middle,Left,Right) };
	auto RSum{ Query_Sum(Node * 2 + 1,Middle + 1,End,Left,Right) };

	return LSum + RSum;
}

void Solve()
{
	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	SegTree.resize(TreeSize, 0);
	InitTree(1, 0, N - 1);

	for (int i{ 0 }; i < Q; ++i)
	{
		LL Start, End, Idx, Val;

		cin >> Start >> End >> Idx >> Val;

		if (Start > End)
			swap(Start, End);

		cout << Query_Sum(1, 0, N - 1, Start - 1, End - 1) << endl;

		LL QueryVal{ Query(1,0,N - 1,Idx - 1) };
		LL Diff{ Val - QueryVal };
		Change(1, 0, N - 1, Idx - 1, Diff);
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