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
#define MAX 2'000'000

int N, Size;
vector<int> SegTree;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(MAX)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize);
}

void Update(int Val)
{
	for (SegTree[Val += Size] += 1; Val > 1; Val >>= 1)
	{
		SegTree[Val >> 1] = SegTree[Val] + SegTree[Val ^ 1];
	}
}

int Query(int Idx)
{
	int Node{ 1 };

	while (true)
	{
		SegTree[Node] -= 1;

		if (Node >= Size)
			break;

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

	return Node - Size;
}

void Solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		int Type;
		cin >> Type;

		if (Type == 1)
		{
			int Val;
			cin >> Val;

			Update(Val);
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