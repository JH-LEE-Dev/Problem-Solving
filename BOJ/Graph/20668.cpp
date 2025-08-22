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
#include <sstream>

using namespace std;
using LL = long long;
using Vertex = tuple<LL, int, int>;

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 10'001

int N, M;
vector<vector<tuple<int, LL, int>>> Edges(MAX, vector<tuple<int, LL, int>>());
vector<vector<LL>> Dist(MAX, vector<LL>(11, INF));
LL Result{ 0 };
LL TenFactorial{ 3628800 };

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		LL Src, Dst, W, Limit;

		cin >> Src >> Dst >> W >> Limit;
		W *= TenFactorial;
		Edges[Src].push_back({ Dst,W,Limit });
		Edges[Dst].push_back({ Src,W,Limit });
	}
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,1,1 });
	Dist[1][1] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurSpeed{ get<2>(Cur) };

		if (Dist[Src][CurSpeed] < CurDist)
			continue;

		if (Src == N)
		{
			Result = CurDist;
			return;
		}

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ get<0>(Edge) };
			auto W{ get<1>(Edge) };
			auto Limit{ get<2>(Edge) };
			auto NewSpeed{ CurSpeed };
			auto NewDist{ CurDist };

			//속도 유지
			NewDist = CurDist + ((LL)W / NewSpeed);

			if (NewSpeed <= Limit && Dist[Dst][NewSpeed] > NewDist)
			{
				Dist[Dst][NewSpeed] = NewDist;
				PQ.push({ NewDist,Dst,NewSpeed });
			}

			//속도 증가
			NewSpeed = CurSpeed + 1;
			NewDist = CurDist + ((LL)W / NewSpeed);

			if (NewSpeed <= Limit && Dist[Dst][NewSpeed] > NewDist)
			{
				Dist[Dst][NewSpeed] = NewDist;
				PQ.push({ NewDist,Dst,NewSpeed });
			}

			//속도 감소
			if (CurSpeed > 1)
			{
				NewSpeed = CurSpeed - 1;
				NewDist = CurDist + ((LL)W / NewSpeed);

				if (NewSpeed <= Limit && Dist[Dst][NewSpeed] > NewDist)
				{
					Dist[Dst][NewSpeed] = NewDist;
					PQ.push({ NewDist,Dst,NewSpeed });
				}
			}
		}
	}
}

void Solve()
{
	Dijkstra();
	LL Integer{ Result / TenFactorial };
	cout << Integer;

	LL Remainder{ Result % TenFactorial };
	stringstream ss;
	ss << fixed << setprecision(9) << (long double)Remainder / TenFactorial;
	cout << ss.str().substr(1);
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