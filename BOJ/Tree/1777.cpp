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

int N, Size;
vector<int> SegTree;
vector<int> Num;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize, 1);

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Num.push_back(Temp);
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
	for (SegTree[Idx += Size] = 0; Idx > 1; Idx >>= 1)
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
		{
			Node <<= 1;
		}
		else
		{
			Idx -= SegTree[Node << 1];
			Node = Node << 1;
			++Node;
		}
	}

	return Node - Size;
}

void Solve()
{
	InitTree();
	vector<int> Result(N + 1);

	for (int i{ 0 }; i < N; ++i)
	{
		auto Cnt{ Num[N - 1 - i] };

		int Idx{ Query(Cnt + 1) };

		Update(Idx);
		Result[N - Idx - 1] = N - i;
	}

	for (int i{ 0 }; i < N; ++i)
	{
		cout << Result[i] << ' ';
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