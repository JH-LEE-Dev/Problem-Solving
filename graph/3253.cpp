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
using Vertex = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N, A, B;
vector<vector<int>> Edges(MAX, vector<int>());
vector<int> Dist(MAX, INF);

void Input()
{
	cin >> N >> A >> B;

	for (int i{ 0 }; i < N; ++i)
	{
		int Ki;
		cin >> Ki;

		for (int j{ 0 }; j < Ki; ++j)
		{
			int Dst;
			cin >> Dst;

			Edges[i + 1].push_back(Dst);
		}
	}
}

void Bfs()
{
	deque<Vertex> DQ;
	DQ.push_front({ 0,A });
	Dist[A] = 0;

	while (DQ.empty() == false)
	{
		auto Cur{ DQ.front() };
		DQ.pop_front();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist[Src] < CurDist)
			continue;

		if (Src == B)
		{
			cout << CurDist;
			return;
		}

		for (int i{ 0 }; i < Edges[Src].size(); ++i)
		{
			auto Dst{ Edges[Src][i] };

			if (i == 0)
			{
				if (Dist[Dst] > CurDist)
				{
					Dist[Dst] = CurDist;
					DQ.push_front({ CurDist,Dst });
				}
			}
			else
			{
				auto NewDist{ CurDist + 1 };

				if (Dist[Dst] > NewDist)
				{
					Dist[Dst] = NewDist;
					DQ.push_back({ NewDist,Dst });
				}
			}
		}
	}

	cout << -1;
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