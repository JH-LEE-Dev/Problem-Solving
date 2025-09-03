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
using State = tuple<LL, int>;

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 200'001

LL N, M;
LL S, T, L, K;
vector<vector<pair<LL, LL>>> Edges(MAX, vector<pair<LL, LL>>());
vector<LL> Dist_F(MAX, INF);
vector<LL> Dist_R(MAX, INF);


void Input()
{
	cin >> N >> M;
	cin >> S >> T >> L >> K;

	for (int i{ 0 }; i < M; ++i)
	{
		LL Src, Dst, W;
		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });
	}
}

void Dijkstra()
{
	priority_queue<State, vector<State>, greater<State>> PQ;
	PQ.push({ 0,S });
	Dist_F[S] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist_F[Src] < CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };

			if (Dist_F[Dst] > NewDist)
			{
				Dist_F[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
			}
		}
	}

	PQ.push({ 0,T });
	Dist_R[T] = 0;

	while (PQ.empty() == false)
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<1>(Cur) };
		auto CurDist{ get<0>(Cur) };

		if (Dist_R[Src] < CurDist)
			continue;

		for (auto& Edge : Edges[Src])
		{
			auto Dst{ Edge.first };
			auto W{ Edge.second };
			auto NewDist{ CurDist + W };

			if (Dist_R[Dst] > NewDist)
			{
				Dist_R[Dst] = NewDist;
				PQ.push({ NewDist,Dst });
			}
		}
	}
}

int UpperBound(LL Target)
{
	int Left{ 0 };
	int Right{ (int)N - 1 };

	while (Left <= Right)
	{
		int Middle{ (Left + Right) / 2 };

		if (Target >= Dist_R[Middle])
			Left = Middle + 1;
		else
			Right = Middle - 1;
	}

	return Left;
}

void Solve()
{
	Dijkstra();

	LL Result{ 0 };

	if (Dist_F[T] <= K)
	{
		cout << N * (N - 1) / 2;
		return;
	}

	sort(Dist_R.begin(), Dist_R.end());

	for (int U{ 1 }; U <= N; ++U)
	{
		if (Dist_F[U] == INF)
			continue;

		LL Target{ K - L - Dist_F[U] };

		Result += UpperBound(Target);
	}

	cout << Result;
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