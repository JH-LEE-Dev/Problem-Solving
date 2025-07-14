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

int N, M, Size;
vector<pair<int, int>> SegTree;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize);

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		SegTree[i + Size] = { Temp % 2 == 0,Temp % 2 == 1 };
	}
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		SegTree[i].first = SegTree[i << 1].first + SegTree[i << 1 | 1].first;
		SegTree[i].second = SegTree[i << 1].second + SegTree[i << 1 | 1].second;
	}
}

void Update(int Idx, int Val)
{
	for (SegTree[Idx += Size] = { Val % 2 == 0,Val % 2 == 1 }; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1].first = SegTree[Idx].first + SegTree[Idx ^ 1].first;
		SegTree[Idx >> 1].second = SegTree[Idx].second + SegTree[Idx ^ 1].second;
	}
}

int Query(int Start, int End, int Type)
{
	int Ret{ 0 };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			if (Type == 2)
			{
				Ret += SegTree[Start].first;
				++Start;
			}
			else
			{
				Ret += SegTree[Start].second;
				++Start;
			}
		}

		if (End & 1)
		{
			if (Type == 2)
			{
				--End;
				Ret += SegTree[End].first;
			}
			else
			{
				--End;
				Ret += SegTree[End].second;
			}
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
			int Idx, Val;
			cin >> Idx >> Val;

			Update(Idx - 1, Val);
		}
		else
		{
			int Start, End;
			cin >> Start >> End;

			cout << Query(Start - 1, End, Type) << endl;
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