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

int N, D, Size;
vector<LL> SegTree;
vector<LL> Arr;

void Input()
{
	cin >> N >> D;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (1 + TreeHeight) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize, -INF);

	for (int i{ 0 }; i < N; ++i)
	{
		LL Temp;

		cin >> Temp;
		Arr.push_back(Temp);
	}
}

void Update(int Idx, LL Val)
{
	for (SegTree[Idx += Size] = Val; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1] = max(SegTree[Idx], SegTree[Idx ^ 1]);
	}
}

LL Query(int Start, int End)
{
	LL Ret{ -INF };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			Ret = max(SegTree[Start], Ret);
			++Start;
		}

		if (End & 1)
		{
			--End;
			Ret = max(SegTree[End], Ret);
		}
	}

	return Ret;
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		int Start{ max(0,i - D) };
		int End{ i };

		LL Sum{ Query(Start,End) };

		if (i == 0)
			Sum = 0;

		LL TotalSum{ max(Sum + Arr[i],Arr[i]) };

		Update(i, TotalSum);
	}

	cout << Query(0, N);
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