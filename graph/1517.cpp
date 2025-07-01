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
#define MAX 500'001

int N;
vector<pair<int, int>> Arr;
vector<LL> SegTree;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back({ Temp,i });
	}
}

void Update(int Node, int Start, int End, int Idx)
{
	if (Start == End)
	{
		SegTree[Node] = 1;

		return;
	}

	int Middle{ (Start + End) / 2 };

	if (Middle >= Idx)
		Update(Node * 2, Start, Middle, Idx);
	else
		Update(Node * 2 + 1, Middle + 1, End, Idx);

	SegTree[Node] = SegTree[Node * 2] + SegTree[Node * 2 + 1];
}

LL Query(int Node, int Start, int End, int Left, int Right)
{
	if (Start > End || End < Left)
		return 0;

	if (Start >= Left && End <= Right)
		return SegTree[Node];

	int Middle{ (Start + End) / 2 };

	auto LSum{ Query(Node * 2,Start,Middle,Left,Right) };
	auto RSum{ Query(Node * 2 + 1,Middle + 1,End,Left,Right) };

	return SegTree[Node] = LSum + RSum;
}

void Solve()
{
	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	SegTree.resize(TreeSize);

	sort(Arr.begin(), Arr.end());

	LL Result{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		auto Idx{ Arr[i].second };
		Result += Query(1, 0, N - 1, Idx, N - 1);
		Update(1, 0, N - 1, Idx - 1);
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