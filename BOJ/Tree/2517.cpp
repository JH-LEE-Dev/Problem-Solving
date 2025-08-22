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

int N, Size;
vector<int> SegTree;
vector<int> Arr;
vector<int> ForIndex;
map<int, int> Index;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize);

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back(Temp);
		ForIndex.push_back(Temp);
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
	sort(ForIndex.begin(), ForIndex.end());

	for (int i{ 0 }; i < N; ++i)
	{
		Index[ForIndex[i]] = i;
	}

	for (int i{ 0 }; i < N; ++i)
	{
		Update(Index[Arr[i]]);

		cout << Query(Index[Arr[i]], N) << endl;
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