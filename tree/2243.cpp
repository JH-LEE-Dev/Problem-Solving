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
using ll = long long;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 1'000'000

int N;
vector<ll> SegmentTree;

int Query(int Node, int Start, int End, int Index)
{
	if (Start == End)
		return Start;

	int Middle{ (Start + End) / 2 };

	if (SegmentTree[Node * 2] >= Index)
		return Query(Node * 2, Start, Middle, Index);
	else
		return Query(Node * 2 + 1, Middle + 1, End, Index - SegmentTree[Node * 2]);
}

void Update(int Node, int Start, int End, int Idx, int Cnt)
{
	if (Idx < Start || Idx > End)
		return;

	SegmentTree[Node] += Cnt;

	if (Start != End)
	{
		int Middle{ (Start + End) / 2 };

		Update(Node * 2, Start, Middle, Idx, Cnt);
		Update(Node * 2 + 1, Middle + 1, End, Idx, Cnt);
	}
}

void input()
{
	cin >> N;
}

void solve()
{
	int Height{ (int)ceil(log2(MAX)) };
	int TreeSize{ 1 << (Height + 1) };
	SegmentTree.resize(TreeSize, 0);

	for (int i{ 0 }; i < N; ++i)
	{
		int Type;
		cin >> Type;

		if (Type == 1)
		{
			int Flavor;
			cin >> Flavor;
			int Pos{ Query(1, 1, MAX, Flavor) };

			cout << Pos << endl;
			Update(1, 1, MAX, Pos, -1);
		}
		else
		{
			int Flavor, Cnt;
			cin >> Flavor >> Cnt;

			Update(1, 1, MAX, Flavor, Cnt);
		}
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}