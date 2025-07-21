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
#define MAX 3'001

int N;
vector<tuple<int, int, int, int>> Lines;
vector<int> Parent(MAX, -1);
vector<int> Rank(MAX, 1);
vector<int> Cnt(MAX, 1);

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int X1, Y1, X2, Y2;
		cin >> X1 >> Y1 >> X2 >> Y2;

		Lines.push_back({ X1,Y1,X2,Y2 });
	}
}

int CCW(pair<int, int> P1, pair<int, int> P2, pair<int, int> P3)
{
	LL Val{ (P2.first - P1.first) * (P3.second - P1.second) - (P2.second - P1.second) * (P3.first - P1.first) };

	//반시계 방향
	if (Val > 0)
		return 1;
	//일직선 상
	else if (Val == 0)
		return 0;
	else
		//시계 방향
		return -1;
}

bool IsLineCrossing(int Left, int Right)
{
	pair<int, int> P1, P2, P3, P4;

	P1.first = get<0>(Lines[Left]);
	P1.second = get<1>(Lines[Left]);
	P2.first = get<2>(Lines[Left]);
	P2.second = get<3>(Lines[Left]);

	P3.first = get<0>(Lines[Right]);
	P3.second = get<1>(Lines[Right]);
	P4.first = get<2>(Lines[Right]);
	P4.second = get<3>(Lines[Right]);

	int CCW_1{ CCW(P1, P2, P3) * CCW(P1, P2, P4) };
	int CCW_2{ CCW(P3, P4, P1) * CCW(P3, P4, P2) };

	//두 선분이 교차할 가능성이 있음
	if (CCW_1 <= 0 && CCW_2 <= 0)
	{
		//두 선분이 일직선 상에 있을 때,
		if (CCW_1 == 0 && CCW_2 == 0)
		{
			//선분의 범위가 겹치지 않으면 false
			if (max(min(P1.first, P2.first), min(P3.first, P4.first)) <= min(max(P1.first, P2.first), max(P3.first, P4.first)) &&
				max(min(P1.second, P2.second), min(P3.second, P4.second)) <= min(max(P1.second, P2.second), max(P3.second, P4.second)))
				return true;
			else
				return false;
		}
	}
	else
		return false;
}

int Find(int U)
{
	if (Parent[U] == U)
		return U;

	return Parent[U] = Find(Parent[U]);
}

void Merge(int U, int V)
{
	int Par_U{ Find(U) };
	int Par_V{ Find(V) };

	if (Par_U == Par_V)
		return;

	if (Rank[Par_U] > Rank[Par_V])
		swap(Par_U, Par_V);

	Parent[Par_U] = Par_V;

	Cnt[Par_V] += Cnt[Par_U];

	if (Rank[Par_U] == Rank[Par_V])
		++Rank[Par_V];
}

void Solve()
{
	set<int> Cluster;

	for (int i{ 0 }; i < N; ++i)
	{
		Parent[i] = i;
	}

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			if (i == j)
				continue;

			if (IsLineCrossing(i, j))
			{
				Merge(i, j);
			}
		}
	}

	int MaxCnt{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		MaxCnt = max(MaxCnt, Cnt[i]);
		Cluster.insert(Find(i));
	}

	cout << Cluster.size() << endl;
	cout << MaxCnt;
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