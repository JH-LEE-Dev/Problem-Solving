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
using ll = long long;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 1'000'001

ll N, M, K;
vector<ll> Arr;
vector<ll> SegTree;

void Input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		ll Temp;
		cin >> Temp;
		Arr.push_back(Temp);
	}
}

ll InitTree(ll Node, ll Start, ll End)
{
	if (Start == End)
	{
		return SegTree[Node] = Arr[Start];
	}

	ll Middle{ (Start + End) / 2 };
	ll Left{ InitTree(Node * 2,Start,Middle) };
	ll Right{ InitTree(Node * 2 + 1,Middle + 1,End) };

	return SegTree[Node] = Left + Right;
}

ll Query_Sum(ll Node, ll Start, ll End, ll Left, ll Right)
{
	if (End < Left || Start > Right)
		return 0;

	if (Start >= Left && End <= Right)
		return SegTree[Node];

	ll Middle{ (Start + End) / 2 };

	ll L{ Query_Sum(Node * 2,Start,Middle,Left,Right) };
	ll R{ Query_Sum(Node * 2 + 1,Middle + 1,End,Left,Right) };

	return L + R;
}

void Query_Change(ll Node, ll Start, ll End, ll Idx, ll Diff)
{
	if (Idx < Start || Idx > End)
		return;

	if (Start == End)
	{
		SegTree[Node] += Diff;
		return;
	}

	SegTree[Node] += Diff;

	ll Middle{ (Start + End) / 2 };

	Query_Change(Node * 2, Start, Middle, Idx, Diff);
	Query_Change(Node * 2 + 1, Middle + 1, End, Idx, Diff);
}

ll Query(int Node, int Start, int End, int Idx)
{
	if (Start == End)
	{
		return SegTree[Node];
	}

	ll Middle{ (Start + End) / 2 };

	if (Idx <= Middle)
		return  Query(Node * 2, Start, Middle, Idx);
	else
		return 	Query(Node * 2 + 1, Middle + 1, End, Idx);
}

void Solve()
{
	ll TreeHeight{ (ll)ceil(log2(N)) };
	ll TreeSize{ 1 << (TreeHeight + 1) };
	SegTree.resize(TreeSize);
	InitTree(1, 0, N - 1);

	for (int i{ 0 }; i < M + K; ++i)
	{
		ll Type;
		cin >> Type;

		if (Type == 2)
		{
			ll Left, Right;
			cin >> Left >> Right;

			cout << Query_Sum(1, 0, N - 1, Left - 1, Right - 1) << endl;
		}
		else
		{
			ll Idx;
			ll Value;
			cin >> Idx >> Value;

			ll Target{ Query(1,0,N - 1,Idx - 1) };
			ll Diff{ Value - Target };

			Query_Change(1, 0, N - 1, Idx - 1, Diff);
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