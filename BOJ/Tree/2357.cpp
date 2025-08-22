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
#define MAX 100'001

int N, M;
vector<int> Arr;
vector<int> SegTree_Max;
vector<int> SegTree_Min;
vector<pair<int, int>> Q;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back(Temp);
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int Start, End;
		cin >> Start >> End;

		Q.push_back({ Start,End });
	}
}

int InitTree_MAX(int Node, int Start, int End)
{
	if (Start == End)
		return SegTree_Max[Node] = Arr[Start];

	int Middle{ (Start + End) / 2 };
	int Left{ InitTree_MAX(Node * 2,Start,Middle) };
	int Right{ InitTree_MAX(Node * 2 + 1,Middle + 1,End) };

	return SegTree_Max[Node] = max(Left, Right);
}

int Query_MAX(int Node, int Start, int End, int Left, int Right)
{
	if (Start > Right || End < Left)
		return 0;

	if (Start >= Left && End <= Right)
		return SegTree_Max[Node];

	int Middle{ (Start + End) / 2 };
	int L{ Query_MAX(Node * 2,Start,Middle,Left,Right) };
	int R{ Query_MAX(Node * 2 + 1,Middle + 1,End,Left,Right) };

	return max(L, R);
}

int InitTree_MIN(int Node, int Start, int End)
{
	if (Start == End)
		return SegTree_Min[Node] = Arr[Start];

	int Middle{ (Start + End) / 2 };
	int Left{ InitTree_MIN(Node * 2,Start,Middle) };
	int Right{ InitTree_MIN(Node * 2 + 1,Middle + 1,End) };

	return SegTree_Min[Node] = min(Left, Right);
}

int Query_MIN(int Node, int Start, int End, int Left, int Right)
{
	if (Start > Right || End < Left)
		return INF;

	if (Start >= Left && End <= Right)
		return SegTree_Min[Node];

	int Middle{ (Start + End) / 2 };
	int L{ Query_MIN(Node * 2,Start,Middle,Left,Right) };
	int R{ Query_MIN(Node * 2 + 1,Middle + 1,End,Left,Right) };

	return min(L, R);
}

void Solve()
{
	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	SegTree_Max.resize(TreeSize);
	SegTree_Min.resize(TreeSize);

	InitTree_MAX(1, 0, N - 1);
	InitTree_MIN(1, 0, N - 1);

	for (int i{ 0 }; i < M; ++i)
	{
		int Start{ Q[i].first - 1 };
		int End{ Q[i].second - 1 };

		int MaxVal{ Query_MAX(1,0,N - 1,Start,End) };
		int MinVal{ Query_MIN(1,0,N - 1,Start,End) };

		cout << MinVal << ' ' << MaxVal << endl;
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