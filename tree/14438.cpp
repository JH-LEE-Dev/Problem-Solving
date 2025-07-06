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

int Size, N, M;
vector<LL> SegTree;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;

	SegTree.resize(TreeSize, INF);

	for (int i{ 0 }; i < N; ++i)
	{
		LL Temp;
		cin >> Temp;

		SegTree[Size + i] = Temp;
	}
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		SegTree[i] = min(SegTree[i << 1], SegTree[i << 1 | 1]);
	}
}

void Update(int Idx, LL Val)
{
	for (SegTree[Idx += Size] = Val; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1] = min(SegTree[Idx], SegTree[Idx ^ 1]);
	}
}

LL Query(int Start, int End)
{
	LL Ret{ INF };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			Ret = min(SegTree[Start], Ret);
			++Start;
		}

		if (End & 1)
		{
			--End;
			Ret = min(SegTree[End], Ret);
		}
	}

	return Ret;
}

void Solve()
{
	InitTree();

	cin >> M;

	for (int i{ 0 }; i < M; ++i)
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
			int Start, End;
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