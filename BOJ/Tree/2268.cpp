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

int N, M;
vector<LL> Arr;
vector<LL> SegTree;
int Size;

void Input()
{
	cin >> N >> M;
}

void InitTree()
{
	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize);
}

void Update(int Idx, LL Val)
{
	for (SegTree[Idx += Size] = Val; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1] = SegTree[Idx] + SegTree[Idx ^ 1];
	}
}

LL Query(int Start, int End)
{
	LL Ret{ 0 };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			Ret += SegTree[Start];
			++Start;
		}

		if (End & 1)
		{
			--End;
			Ret += SegTree[End];
		}
	}

	return Ret;
}

void Solve()
{
	InitTree();

	for (int i{ 0 }; i < M; ++i)
	{
		int Type;
		cin >> Type;

		if (Type == 0)
		{
			int Start, End;
			cin >> Start >> End;

			if (Start > End)
				swap(Start, End);

			cout << Query(Start - 1, End) << endl;
		}
		else
		{
			LL Idx, Val;

			cin >> Idx >> Val;

			Update(Idx - 1, Val);
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