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

int Size, N, K;
vector<int> SegTree;

void Input()
{
	SegTree.clear();

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	SegTree.resize(TreeSize);
	Size = 1 << TreeHeight;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		if (Temp > 0)
			SegTree[i + Size] = 1;

		if (Temp == 0)
			SegTree[i + Size] = 0;

		if (Temp < 0)
			SegTree[i + Size] = -1;
	}
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		SegTree[i] = SegTree[i << 1] * SegTree[i << 1 | 1];
	}
}

void Update(int Idx, int Val)
{
	for (SegTree[Idx += Size] = Val; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1] = SegTree[Idx] * SegTree[Idx ^ 1];
	}
}

LL Query(int Start, int End)
{
	LL Ret{ 1 };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			Ret *= SegTree[Start];
			++Start;
		}

		if (End & 1)
		{
			--End;
			Ret *= SegTree[End];
		}
	}

	return Ret;
}

void Solve()
{
	while (cin >> N >> K)
	{
		Input();

		InitTree();

		string Str;

		for (int i{ 0 }; i < K; ++i)
		{
			char Type;

			cin >> Type;

			if (Type == 'C')
			{
				int Idx, Val;
				cin >> Idx >> Val;

				if (Val > 0)
					Update(Idx - 1, 1);

				if (Val == 0)
					Update(Idx - 1, 0);

				if (Val < 0)
					Update(Idx - 1, -1);
			}
			else
			{
				int Start, End;
				cin >> Start >> End;

				LL Result{ Query(Start - 1,End) };

				if (Result == 0)
				{
					Str += '0';
				}

				if (Result > 0)
				{
					Str += '+';
				}

				if (Result < 0)
				{
					Str += '-';
				}
			}
		}

		for (int i{ 0 }; i < Str.length(); ++i)
		{
			cout << Str[i];
		}

		cout << endl;
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