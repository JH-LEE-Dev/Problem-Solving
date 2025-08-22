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
#define MAX 1'000'001

int N, Size;
vector<LL> Arr(MAX, -1);
vector<LL> SegTree;
vector<pair<int, int>> PairNum;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	SegTree.resize(TreeSize);
	Size = 1 << TreeHeight;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr[Temp] = i;
	}

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		PairNum.push_back({ i,Arr[Temp] });
	}
}

void Update(int Idx)
{
	for (SegTree[Idx += Size] = 1; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1] = SegTree[Idx] + SegTree[Idx ^ 1];
	}
}

LL Query(int Start, int End)
{
	LL Ret{ 0 };

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

	sort(PairNum.begin(), PairNum.end());

	for (int i{ 0 }; i < N; ++i)
	{
		int OriginIdx{ PairNum[i].second };
		Update(OriginIdx - 1);

		Result += Query(OriginIdx, N);
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