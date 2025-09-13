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
#define INF numeric_limits<LL>::max()
#define MAX 10'001

int N;
vector<vector<pair<LL, LL>>> Edges;
vector<int> Cnt;
LL Sum;
LL Result{ INF };
bool bValid{ true };

void Input()
{
	Result = INF;
	Edges = vector<vector<pair<LL, LL>>>(MAX, vector<pair<LL, LL>>());
	Cnt = vector<int>(MAX, 0);
	Sum = 0;

	cin >> N;

	if (N == 0)
	{
		bValid = false;
		return;
	}

	for (int i{ 0 }; i < N - 1; ++i)
	{
		int Src, Dst, W;
		cin >> Src >> Dst >> W;

		Edges[Src].push_back({ Dst,W });
		Edges[Dst].push_back({ Src,W });
	}
}

void CalcSum_Cnt(int Src, int From, LL Dist)
{
	Cnt[Src] = 1;

	Sum += Dist;

	for (auto& Edge : Edges[Src])
	{
		auto Dst{ Edge.first };
		auto W{ Edge.second };

		if (Dst == From)
			continue;

		CalcSum_Cnt(Dst, Src, Dist + W);
		Cnt[Src] += Cnt[Dst];
	}
}

void CalcResult(int Src, int From, LL Total)
{
	Result = min(Result, Total);

	for (auto& Edge : Edges[Src])
	{
		auto Dst{ Edge.first };
		auto W{ Edge.second };

		if (Dst == From)
			continue;

		CalcResult(Dst, Src, Total - (Cnt[Dst] * W) + ((N - Cnt[Dst]) * W));
	}
}

void Solve()
{
	while (true)
	{
		Input();

		if (bValid == false)
			return;

		CalcSum_Cnt(0, -1, 0);
		CalcResult(0, -1, Sum);

		cout << Result << endl;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}