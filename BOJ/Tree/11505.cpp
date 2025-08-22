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
#define DIV 1'000'000'007

int N, M, K;
vector<int> Arr(MAX, 0);
vector<int> SegTree;

void Input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> Arr[i];
	}
}

int InitTree(int Node, int Start, int End)
{
	if (Start == End)
	{
		return SegTree[Node] = Arr[Start];
	}

	int Middle{ (Start + End) / 2 };
	int Left{ InitTree(Node * 2,Start,Middle) % DIV };
	int Right{ InitTree(Node * 2 + 1,Middle + 1,End) % DIV };

	return SegTree[Node] = ((LL)Left * (LL)Right) % DIV;
}

int Update(int Node, int Start, int End, int Idx, int Value)
{
	if (Start > Idx || End < Idx)
		return SegTree[Node];

	if (Start == End)
	{
		return SegTree[Node] = Value;
	}

	int Middle{ (Start + End) / 2 };
	int Left{ Update(Node * 2, Start, Middle, Idx,Value) % DIV };
	int Right{ Update(Node * 2 + 1, Middle + 1, End, Idx,Value) % DIV };

	return SegTree[Node] = ((LL)Left * (LL)Right) % DIV;
}

int Query_Sum(int Node, int Start, int End, int Left, int Right)
{
	if (Start > Right || End < Left)
		return 1;

	if (Left <= Start && End <= Right)
		return SegTree[Node];

	int Middle{ (Start + End) / 2 };
	int L{ Query_Sum(Node * 2,Start,Middle,Left,Right) % DIV };
	int R{ Query_Sum(Node * 2 + 1,Middle + 1,End,Left,Right) % DIV };

	return ((LL)L * (LL)R) % DIV;
}

void Solve()
{
	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	SegTree.resize(TreeSize);

	InitTree(1, 0, N - 1);

	for (int i{ 0 }; i < M + K; ++i)
	{
		int Type, A, B;
		cin >> Type >> A >> B;

		if (Type == 1)
		{
			Update(1, 0, N - 1, A - 1, B);
		}
		else
		{
			cout << Query_Sum(1, 0, N - 1, A - 1, B - 1) << endl;
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