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
using Line = tuple<int, int, int, int>;
using State = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 5'001

int N, M, K;
vector<Line> Lines;
vector<bool> Visited(MAX, false);
pair<int, int> Start;
pair<int, int> End;

void Input()
{
	cin >> N >> M;

	cin >> K;

	for (int i{ 0 }; i < K; ++i)
	{
		int Idx, X1, Y1, X2, Y2;
		cin >> Idx >> X1 >> Y1 >> X2 >> Y2;

		if (X1 == X2)
		{
			if (Y1 > Y2)
			{
				swap(X1, X2);
				swap(Y1, Y2);
			}
		}
		else
		{
			if (X1 > X2)
			{
				swap(X1, X2);
				swap(Y1, Y2);
			}
		}

		Lines.push_back({ X1,Y1,X2,Y2 });
	}

	cin >> Start.first >> Start.second >> End.first >> End.second;
}

int CCW(pair<LL, LL> P1, pair<LL, LL> P2, pair<LL, LL> P3)
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
		else
			return true;
	}
	else
		return false;
}

void Bfs()
{
	queue<State> Q;

	for (int i{ 0 }; i < K; ++i)
	{
		auto CurLine{ Lines[i] };
		auto [X1, Y1, X2, Y2] {CurLine};

		if (Start.first >= X1 && Start.first <= X2 &&
			Start.second >= Y1 && Start.second <= Y2)
		{
			Visited[i] = true;
			Q.push({ 1,i });
		}
	}

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto [CurDist, CurIdx] {Cur};
		auto [X1, Y1, X2, Y2] {Lines[CurIdx]};

		if (End.first >= X1 && End.first <= X2 &&
			End.second >= Y1 && End.second <= Y2)
		{
			cout << CurDist;
			return;
		}

		for (int i{ 0 }; i < K; ++i)
		{
			if (CurIdx == i || Visited[i] == true)
				continue;

			auto NxtLine{ Lines[i] };

			if (IsLineCrossing(CurIdx, i))
			{
				Q.push({ CurDist + 1,i });
				Visited[i] = true;
			}
		}
	}
}

void Solve()
{
	Bfs();
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