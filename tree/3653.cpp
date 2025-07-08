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
#define MAX 100'000

int Size, T, N, M;
vector<int> SegTree;
vector<int> Idx;

void Input()
{
	cin >> T;
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
	for (int i{ 0 }; i < T; ++i)
	{
		SegTree.clear();
		Idx.clear();

		cin >> N >> M;

		int TreeHeight{ (int)ceil(log2(2 * MAX)) };
		int TreeSize{ 1 << (TreeHeight + 1) };
		Size = 1 << TreeHeight;
		SegTree.resize(TreeSize, 0);
		Idx.resize(MAX, 0);

		for (int j{ 0 }; j < N; ++j)
		{
			Idx[j + 1] = N - j - 1;
			SegTree[Size + j] = 1;
		}

		InitTree();

		for (int j{ 0 }; j < M; ++j)
		{
			int Temp;
			cin >> Temp;

			cout << Query(Idx[Temp], 2 * MAX) - 1 << endl;

			Update(Idx[Temp], -1);
			Idx[Temp] = N + j;
			Update(N + j, 1);
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