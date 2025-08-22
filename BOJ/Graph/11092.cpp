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
using Vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 15

int N;
vector<vector<int>> Dist(2, vector<int>(1 << MAX, INF));
vector<int> Times(MAX, 0);

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> Times[i];
	}
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;

	for (int i{ 0 }; i < N; ++i)
	{
		int State_A{ 1 << i };

		for (int j{ 0 }; j < N; ++j)
		{
			if (i == j)
				continue;

			int State_B{ 1 << j };

			int CombinedState{ State_A | State_B };

			PQ.push({ max(Times[i],Times[j]),CombinedState,1 });

			Dist[1][CombinedState] = max(Times[i], Times[j]);
		}
	}

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto CurState{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurType{ get<2>(Cur) };

		if (Dist[CurType][CurState] < CurDist)
			continue;

		if (CurState == (1 << N) - 1 && CurType == 1)
		{
			cout << CurDist;
			return;
		}

		if (CurType == 0)
		{
			for (int i{ 0 }; i < N; ++i)
			{
				int State_A{ 1 << i };

				if ((CurState & State_A) == State_A)
					continue;

				State_A = CurState | State_A;

				for (int j{ 0 }; j < N; ++j)
				{
					if (i == j)
						continue;

					int State_B{ 1 << j };

					if ((CurState & State_B) == State_B)
						continue;

					int CombinedState{ State_A | State_B };
					int NewDist{ CurDist + max(Times[i], Times[j]) };

					if (Dist[1][CombinedState] > NewDist)
					{
						PQ.push({ NewDist,CombinedState,1 });
						Dist[1][CombinedState] = NewDist;
					}
				}
			}
		}
		else
		{
			for (int i{ 0 }; i < N; ++i)
			{
				int State{ 1 << i };

				if ((CurState & State) != State)
					continue;

				int NewState = (CurState & (~State));
				int NewDist{ CurDist + Times[i] };

				if (Dist[0][NewState] > NewDist)
				{
					PQ.push({ NewDist,NewState,0 });
					Dist[0][NewState] = NewDist;
				}
			}
		}
	}
}

void Solve()
{
	Dijkstra();
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