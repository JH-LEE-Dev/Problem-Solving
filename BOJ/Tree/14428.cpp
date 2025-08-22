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

int N, Size, M;
vector<int> Arr;
vector<pair<int, int>> SegTree;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	Size = 1 << (TreeHeight + 1);
	SegTree.resize(Size, { INF,INF });
	Size = 1 << TreeHeight;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back(Temp);
		SegTree[i + Size] = { Temp,i };
	}

	cin >> M;
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		SegTree[i] = min(SegTree[i << 1], SegTree[i << 1 | 1]);
	}
}

int Query(int Start, int End)
{
	pair<int, int> Ret{ INF,INF };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			Ret = min(Ret, SegTree[Start]);
			++Start;
		}

		if (End & 1)
		{
			--End;
			Ret = min(Ret, SegTree[End]);
		}
	}

	return Ret.second + 1;
}

void Update(int Idx, int Val)
{
	for (SegTree[Idx += Size] = { Val,SegTree[Idx + Size].second }; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1] = min(SegTree[Idx], SegTree[Idx ^ 1]);
	}
}

void Solve()
{
	InitTree();

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