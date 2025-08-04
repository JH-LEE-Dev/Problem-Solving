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
#define MAX 500'001

int N, M, Size;
vector<int> SegTree;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize);

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> SegTree[i + Size];
	}

	cin >> M;
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		SegTree[i] = SegTree[i << 1] + SegTree[i << 1 | 1];
	}
}

void Update(int Idx, int Val)
{
	for (SegTree[Idx += Size] += Val; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1] = SegTree[Idx] + SegTree[Idx ^ 1];
	}
}

int Query(int Idx)
{
	int Node{ 1 };

	while (true)
	{
		if (Node >= Size)
			break;

		if (SegTree[Node << 1] >= Idx)
			Node <<= 1;
		else
		{
			Idx -= SegTree[Node << 1];
			Node <<= 1;
			++Node;
		}
	}

	return Node - Size + 1;
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
			int Idx;
			cin >> Idx;

			cout << Query(Idx) << endl;
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