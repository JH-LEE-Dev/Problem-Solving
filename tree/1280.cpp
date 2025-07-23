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
#define MAX 200'000
#define MOD 1'000'000'007

int N, Size;
vector<LL> Arr;
vector<pair<LL, LL>> SegTree;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(MAX)) };
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
	for (SegTree[Idx + Size].first += Idx, SegTree[Idx += Size].second += 1; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1].first = SegTree[Idx].first + SegTree[Idx ^ 1].first;
		SegTree[Idx >> 1].second = SegTree[Idx].second + SegTree[Idx ^ 1].second;
	}
}

pair<LL, LL> Query(int Start, int End)
{
	LL Ret{ 0 };
	LL Cnt{ 0 };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			Ret += SegTree[Start].first;
			Cnt += SegTree[Start].second;

			++Start;
		}

		if (End & 1)
		{
			--End;

			Ret += SegTree[End].first;
			Cnt += SegTree[End].second;
		}
	}

	return { Ret,Cnt };
}

void Solve()
{
	LL Result{ 1 };
	Update(Arr[0]);

	for (int i{ 1 }; i < N; ++i)
	{
		Update(Arr[i]);

		auto Left{ Query(0,Arr[i]) };
		auto Right{ Query(Arr[i] + 1,MAX) };

		LL LeftSum{ Left.first };
		LL RightSum{ Right.first };
		LL LeftCnt{ Left.second };
		LL RightCnt{ Right.second };

		LL TempResult{ abs(LeftSum - LeftCnt * Arr[i]) + abs(RightSum - RightCnt * Arr[i]) };
		TempResult %= MOD;
		Result = (Result * TempResult) % MOD;
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