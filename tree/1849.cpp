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
vector<int> Result(MAX, -1);

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize, 1);
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		SegTree[i] = SegTree[i << 1] + SegTree[i << 1 | 1];
	}
}

int Update(int Idx)
{
	int Node{ 1 };

	while (true)
	{
		if (Node >= Size)
		{
			SegTree[Node] = 0;
			return Node - Size;
		}

		--SegTree[Node];

		if (SegTree[Node << 1] >= Idx)
		{
			Node <<= 1;
		}
		else
		{
			Idx -= SegTree[Node << 1];
			Node <<= 1;
			++Node;
		}
	}
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		SegTree[i + Size] = 1;
	}

	InitTree();

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		auto Idx{ Update(Temp + 1) };
		Result[Idx] = i + 1;
	}

	for (int i{ 0 }; i < N; ++i)
	{
		cout << Result[i] << endl;
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