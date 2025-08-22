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
using Vertex = tuple<LL, int, int>;

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 200'001

int N, X, Y, K;
vector<vector<tuple<int, int, int>>> Edges(MAX, vector<tuple<int, int, int>>());
vector<LL> Dist(MAX, INF);

void Input()
{
	cin >> N >> K >> X >> Y;

	for (int i{ 0 }; i < X; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W,0 });
		Edges[Dst].push_back({ Src,W,0 });
	}

	for (int i{ 0 }; i < Y; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W,1 });
		Edges[Dst].push_back({ Src,W,1 });
	}
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,1,0 });
	Dist[1] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurType{ get<2>(Cur) };

		if (Dist[Src] < CurDist)
			continue;

		if (Src == N)
		{
			cout << CurDist;
			return;
		}

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ get<0>(Edge) };
			auto W{ get<1>(Edge) };
			auto Type{ get<2>(Edge) };
			auto NewDist{ CurDist + W };

			//인도일 때
			if (Type == 0)
			{
				//인도는 아무 때나 갈 수 있음
				if (Dist[Dst] > NewDist)
				{
					Dist[Dst] = NewDist;
					PQ.push({ NewDist,Dst,Type });
				}
			}
			else
			{
				//인도 -> 차도일 때
				if (CurType == 0)
				{
					//첫 차가 지나가기 이전이라면, K까지 기다렸다가 버스 타야 함.
					if (CurDist < K)
					{
						if (Dist[Dst] > NewDist + (K - CurDist))
						{
							Dist[Dst] = NewDist + (K - CurDist);
							PQ.push({ NewDist + (K - CurDist),Dst,Type });
						}
					}
					//K분 후 부터는 차를 마음대로 탈 수 있음.
					else
					{
						if (Dist[Dst] > NewDist)
						{
							Dist[Dst] = NewDist;
							PQ.push({ NewDist,Dst,Type });
						}
					}
				}
				//차도 -> 차도 (아무런 제약 없음)
				else
				{
					if (Dist[Dst] > NewDist)
					{
						Dist[Dst] = NewDist;
						PQ.push({ NewDist,Dst,Type });
					}
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