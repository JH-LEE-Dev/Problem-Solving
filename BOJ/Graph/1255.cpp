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
using Line = tuple<int, int, int, int>;
using State = tuple<float, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define INF_FL numeric_limits<float>::max()
#define MAX 51

int N, M;
vector<tuple<int, int, int>> Vertexes;
vector<Line> Lines;
vector<vector<vector<float>>> Dist(MAX, vector<vector<float>>(101, vector<float>(101, INF_FL)));

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		int X, Y, V;

		char Temp;

		cin >> Temp >> X >> Temp >> Y >> Temp >> V;

		Vertexes.push_back({ X,Y,V });
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int X1, Y1, X2, Y2;

		char Temp;

		cin >> Temp >> X1 >> Temp >> Y1 >> Temp >> Temp >> Temp >> X2 >> Temp >> Y2 >> Temp;

		if (Y1 > Y2)
		{
			swap(Y1, Y2);
			swap(X1, X2);
		}

		Lines.push_back({ X1,Y1,X2,Y2 });
	}
}

int CCW(pair<int, int> P1, pair<int, int> P2, pair<int, int> P3)
{
	int Val{ (P2.first - P1.first) * (P3.second - P1.second) - (P2.second - P1.second) * (P3.first - P1.first) };

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

bool IsLineCrossing(Line Left, Line Right)
{
	pair<int, int> P1, P2, P3, P4;

	P1.first = get<0>(Left);
	P1.second = get<1>(Left);
	P2.first = get<2>(Left);
	P2.second = get<3>(Left);

	P3.first = get<0>(Right);
	P3.second = get<1>(Right);
	P4.first = get<2>(Right);
	P4.second = get<3>(Right);

	int CCW_1{ CCW(P1, P2, P3) * CCW(P1, P2, P4) };
	int CCW_2{ CCW(P3, P4, P1) * CCW(P3, P4, P2) };

	if (CCW_1 < 0 && CCW_2 < 0)
	{
		return true;
	}
	else
		return false;
}

float Dijkstra(int Idx, tuple<int, int, int> Start)
{
	auto Start_X{ get<0>(Start) };
	auto Start_Y{ get<1>(Start) };
	auto V{ get<2>(Start) };

	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ 0,Start_X,Start_Y });
	Dist[Idx][Start_X][Start_Y] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto CurDist{ get<0>(Cur) };
		auto X{ get<1>(Cur) };
		auto Y{ get<2>(Cur) };

		if (Dist[Idx][X][Y] < CurDist)
			continue;

		if (Y == 0)
			return CurDist;

		//Direct
		bool bCrossing{ false };
		Line Direct_Line{ X,Y,X,0 };
		for (auto& L2 : Lines)
		{
			bCrossing = IsLineCrossing(Direct_Line, L2);

			if (bCrossing == true)
				break;
		}

		if (bCrossing == false)
		{
			float Distance{ (float)Y / V };
			auto NewDist{ CurDist + Distance };

			if (Dist[Idx][X][0] > NewDist)
			{
				Dist[Idx][X][0] = NewDist;
				PQ.push({ NewDist,X,0 });
			}
		}


		for (auto& L : Lines)
		{
			auto [X1, Y1, X2, Y2] { L };

			if (Y < Y1)
				continue;

			Line Line_1{ X,Y,X1,Y1 };
			Line Line_2{ X,Y,X2,Y2 };

			bool bCrossing{ false };

			//Line_1
			bCrossing = false;
			for (auto& L2 : Lines)
			{
				bCrossing = IsLineCrossing(Line_1, L2);

				if (bCrossing == true)
					break;
			}

			if (bCrossing == false)
			{
				float Distance{ (float)hypot(abs(X - X1),abs(Y - Y1)) / V };
				auto NewDist{ CurDist + Distance };

				if (Dist[Idx][X1][Y1] > NewDist)
				{
					Dist[Idx][X1][Y1] = NewDist;
					PQ.push({ NewDist,X1,Y1 });
				}
			}



			//Line_2
			bCrossing = false;
			for (auto& L2 : Lines)
			{
				bCrossing = IsLineCrossing(Line_2, L2);

				if (bCrossing == true)
					break;
			}

			if (bCrossing == false)
			{
				float Distance{ (float)hypot(abs(X - X2),abs(Y - Y2)) / V };
				auto NewDist{ CurDist + Distance };

				if (Dist[Idx][X2][Y2] > NewDist)
				{
					Dist[Idx][X2][Y2] = NewDist;
					PQ.push({ NewDist,X2,Y2 });
				}
			}
		}
	}
}

void Solve()
{
	float Result{ 0 };

	if (N == 0 && M == 0)
	{
		cout << fixed << setprecision(1) << Result;
		return;
	}

	for (int i{ 0 }; i < N; ++i)
	{
		Result = max(Dijkstra(i, Vertexes[i]), Result);
	}

	cout << fixed << setprecision(1) << Result;
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