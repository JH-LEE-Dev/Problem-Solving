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

int N, Size;
vector<int> SegTree;
vector<int> Arr;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (1 + TreeHeight) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize);

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;
		Arr.push_back(Temp);
	}
}

void Update(int Idx)
{
	for (SegTree[Idx += Size] = 1; Idx > 1; Idx >>= 1)
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
	LL Result{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		Result += Query(Arr[i] - 1, N);

		Update(Arr[i] - 1);
	}

	cout << Result;
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