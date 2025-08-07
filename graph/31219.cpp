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

#define endl '\n'
#define INF numeric_limits<double>::max()
#define MAX 11

int N;
vector<pair<int, int>> Points;
vector<tuple<int, int, int, int>> Lines;
vector<vector<double>> Dist(MAX, vector<double>(1 << MAX, -1));

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int R, C;
		cin >> R >> C;

		Points.push_back({ R,C });
	}
}

double Dfs(int CurBit, int Src)
{
	pair<int, int> CurPoint{ Points[Src] };

	if (CurBit == (1 << N) - 1)
	{
		return hypot(abs(CurPoint.first - Points[0].first), abs(CurPoint.second - Points[0].second));
	}

	if (Dist[Src][CurBit] != -1)
		return Dist[Src][CurBit];

	Dist[Src][CurBit] = INF;

	for (int i{ 0 }; i < N; ++i)
	{
		if ((CurBit & (1 << i)) == (1 << i))
			continue;

		auto NewBit{ CurBit | (1 << i) };
		auto NxtPoint{ Points[i] };

		auto Distance{ hypot(abs(CurPoint.first - NxtPoint.first),abs(CurPoint.second - NxtPoint.second)) };

		Dist[Src][CurBit] = min(Dist[Src][CurBit], Distance + Dfs(NewBit, i));
	}

	return Dist[Src][CurBit];
}

void Solve()
{
	double Result{ INF };

	cout << fixed << setprecision(7) << Dfs(1, 0);
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