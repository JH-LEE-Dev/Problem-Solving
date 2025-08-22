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

int N, Size;
vector<LL> SegTree_Min;
vector<LL> SegTree_Sum;
vector<LL> Arr;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;
	SegTree_Min.resize(TreeSize);
	SegTree_Sum.resize(TreeSize);
	Arr.resize(TreeSize, INF);

	for (int i{ 0 }; i < N; ++i)
	{
		LL Temp;
		cin >> Temp;

		Arr[i] = Temp;

		SegTree_Min[Size + i] = i;
		SegTree_Sum[Size + i] = Temp;
	}
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		if (Arr[SegTree_Min[i << 1]] < Arr[SegTree_Min[i << 1 | 1]])
			SegTree_Min[i] = SegTree_Min[i << 1];
		else
			SegTree_Min[i] = SegTree_Min[i << 1 | 1];

		SegTree_Sum[i] = SegTree_Sum[i << 1] + SegTree_Sum[i << 1 | 1];
	}
}

LL Query_Min(int Start, int End)
{
	LL Ret{ INF };
	LL MinVal{ INF };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			if (MinVal > Arr[SegTree_Min[Start]])
			{
				MinVal = Arr[SegTree_Min[Start]];
				Ret = SegTree_Min[Start];
			}

			++Start;
		}

		if (End & 1)
		{
			--End;

			if (MinVal > Arr[SegTree_Min[End]])
			{
				MinVal = Arr[SegTree_Min[End]];
				Ret = SegTree_Min[End];
			}
		}
	}

	return Ret;
}

LL Query_Sum(int Start, int End)
{
	LL Ret{ 0 };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			Ret += SegTree_Sum[Start];
			++Start;
		}

		if (End & 1)
		{
			--End;
			Ret += SegTree_Sum[End];
		}
	}

	return Ret;
}

LL Query(int Start, int End)
{
	LL Idx{ Query_Min(Start ,End) };
	LL Sum{ Query_Sum(Start ,End) };

	LL TempResult{ Arr[Idx] * Sum };

	if (Idx > Start)
		TempResult = max(TempResult, Query(Start, Idx));

	if (Idx < End - 1)
		TempResult = max(TempResult, Query(Idx + 1, End));

	return TempResult;
}

void Solve()
{
	InitTree();

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