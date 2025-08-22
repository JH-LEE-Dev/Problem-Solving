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

int N, Size, Q;
vector<pair<int, int>> SegTree;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (1 + TreeHeight) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize, { 0,0 });

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> SegTree[Size + i].first;

		SegTree[Size + i].second = 0;
	}

	cin >> Q;
}

void InitTree()
{
	priority_queue<int, vector<int>, greater<int>> PQ;

	for (int i{ Size - 1 }; i > 0; --i)
	{
		//First Max.
		PQ.push(SegTree[i << 1].first);
		if (SegTree[i << 1].second != 0)
			PQ.push(SegTree[i << 1].second);

		//Second Max.
		PQ.push(SegTree[i << 1 | 1].first);
		if (SegTree[i << 1 | 1].second != 0)
			PQ.push(SegTree[i << 1 | 1].second);

		while (PQ.size() > 2)
		{
			PQ.pop();
		}

		SegTree[i].first = PQ.top();
		PQ.pop();
		SegTree[i].second = PQ.top();
		PQ.pop();
	}
}

void Update(int Idx, int Val)
{
	priority_queue<int, vector<int>, greater<int>> PQ;

	for (SegTree[Idx += Size].first = Val; Idx > 1; Idx >>= 1)
	{
		//First Max.
		PQ.push(SegTree[Idx].first);
		if (SegTree[Idx].second != 0)
			PQ.push(SegTree[Idx].second);

		//Second Max.
		PQ.push(SegTree[Idx ^ 1].first);
		if (SegTree[Idx ^ 1].second != 0)
			PQ.push(SegTree[Idx ^ 1].second);

		while (PQ.size() > 2)
		{
			PQ.pop();
		}

		SegTree[Idx >> 1].first = PQ.top();
		PQ.pop();
		SegTree[Idx >> 1].second = PQ.top();
		PQ.pop();
	}
}

int Query(int Start, int End)
{
	priority_queue<int, vector<int>, greater<int>> PQ;

	int Result{ 0 };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			PQ.push(SegTree[Start].first);
			if (SegTree[Start].second != 0)
				PQ.push(SegTree[Start].second);

			++Start;
		}

		if (End & 1)
		{
			--End;

			PQ.push(SegTree[End].first);
			if (SegTree[End].second != 0)
				PQ.push(SegTree[End].second);
		}

		while (PQ.size() > 2)
		{
			PQ.pop();
		}
	}

	Result += PQ.top();
	PQ.pop();
	Result += PQ.top();
	PQ.pop();

	return Result;
}

void Solve()
{
	InitTree();

	while (Q != 0)
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

		--Q;
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