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
#define MAX 100'001

int N, Size;
vector<int> SegTree;
vector<pair<int, int>> Arr;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (1 + TreeHeight) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize);

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back({ Temp,i });
		SegTree[i + Size] = 1;
	}
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		SegTree[i] = SegTree[i << 1] + SegTree[i << 1 | 1];
	}
}

void Update(int Idx)
{
	for (SegTree[Idx += Size] -= 1; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1] = SegTree[Idx] + SegTree[Idx ^ 1];
	}
}

int Query(int Start, int End)
{
	int Ret{ 0 };

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

	sort(Arr.begin(), Arr.end());

	int LeftPivot{ 0 };
	int RightPivot{ N - 1 };

	for (int i{ 0 }; i < Arr.size(); ++i)
	{
		if (i % 2 == 0)
		{
			int Num{ Arr[LeftPivot].first - 1 };
			int Idx{ Arr[LeftPivot].second };

			int SwapCnt{ Query(0,Idx) };
			Update(Idx);

			cout << SwapCnt << endl;

			++LeftPivot;
		}
		else
		{
			int Num{ Arr[RightPivot].first - 1 };
			int Idx{ Arr[RightPivot].second };

			int SwapCnt{ Query(Idx + 1,N) };
			Update(Idx);

			cout << SwapCnt << endl;

			--RightPivot;
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