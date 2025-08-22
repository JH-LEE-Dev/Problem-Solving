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
#define MAX 100'001

int N;
vector<int> SegTree;
vector<int> Arr;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back(Temp);
	}
}

int InitTree(int Node, int Start, int End)
{
	if (Start == End)
	{
		return SegTree[Node] = Start;
	}

	int Middle{ (Start + End) / 2 };
	int Left{ InitTree(Node * 2,Start,Middle) };
	int Right{ InitTree(Node * 2 + 1,Middle + 1,End) };

	if (Arr[Left] < Arr[Right])
		return SegTree[Node] = Left;
	else
		return SegTree[Node] = Right;
}

int Query(int Node, int Start, int End, int Left, int Right)
{
	if (Start > Right || Left > End)
		return -1;

	if (Left <= Start && Right >= End)
		return SegTree[Node];

	int Middle{ (Start + End) / 2 };
	int L{ Query(Node * 2,Start,Middle,Left,Right) };
	int R{ Query(Node * 2 + 1,Middle + 1,End,Left,Right) };

	if (L == -1)
		return R;
	else if (R == -1)
		return L;

	if (Arr[L] < Arr[R])
		return L;
	else
		return R;
}

int Query_Sum(int Left, int Right)
{
	int MinIdx{ Query(1,0,N - 1,Left,Right) };
	int MaxSquare{ ((Right - Left) + 1) * Arr[MinIdx] };

	if (MinIdx >= Left + 1)
		MaxSquare = max(MaxSquare, Query_Sum(Left, MinIdx - 1));

	if (MinIdx <= Right - 1)
		MaxSquare = max(MaxSquare, Query_Sum(MinIdx + 1, Right));

	return MaxSquare;
}

void Solve()
{
	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	SegTree.resize(TreeSize);
	InitTree(1, 0, N - 1);

	cout << Query_Sum(0, N - 1);
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