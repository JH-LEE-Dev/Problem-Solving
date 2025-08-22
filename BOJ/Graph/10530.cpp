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
#define INF numeric_limits<LL>::max()
#define MAX 100'001

int N, Size;
vector<pair<LL, LL>> SegTree;
LL Result;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (1 + TreeHeight) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize);

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> SegTree[i + Size].first;
		SegTree[i + Size].second = i;
	}
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		SegTree[i] = min(SegTree[i << 1], SegTree[i << 1 | 1]);
	}
}

pair<LL, LL> Query(int Start, int End)
{
	LL Ret{ INF };
	LL MinVal{ INF };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			if (MinVal > SegTree[Start].first)
			{
				MinVal = SegTree[Start].first;
				Ret = SegTree[Start].second;
			}

			++Start;
		}

		if (End & 1)
		{
			--End;

			if (MinVal > SegTree[End].first)
			{
				MinVal = SegTree[End].first;
				Ret = SegTree[End].second;
			}
		}
	}

	return { MinVal,Ret };
}

void Dfs(int Start, int End, int Cnt)
{
	auto Min{ Query(Start,End) };
	auto MinVal{ Min.first };
	auto MinIdx{ Min.second };

	Result = max(Result, MinVal * Cnt);

	if (MinIdx > Start)
	{
		Dfs(Start, MinIdx, MinIdx - Start);
	}

	if (MinIdx < End - 1)
	{
		Dfs(MinIdx + 1, End, End - (MinIdx + 1));
	}
}

void Solve()
{
	InitTree();

	Dfs(0, N, N);

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