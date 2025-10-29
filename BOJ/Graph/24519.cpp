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

#define endl '\n'
#define INF numeric_limits<int>::max()/2
#define MAX 18

int N, M;
vector<vector<int>> Edges(MAX + 5, vector<int>(MAX + 5, INF));
vector<vector<int>> DfsDist(1 << MAX, vector<int>(MAX + 5, -1));

int ResultBit;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst, W;

		cin >> Src >> Dst >> W;

		Edges[Src][Dst] = W;
	}

	ResultBit = (1 << N) - 1;
}

int Dfs(int CurBit, int Src)
{
	if (CurBit == ResultBit)
	{
		if (Edges[Src][1] == INF)
			return INF;
		else
		{
			return DfsDist[CurBit][Src] = Edges[Src][1];
		}
	}

	if (DfsDist[CurBit][Src] != -1)
		return DfsDist[CurBit][Src];

	DfsDist[CurBit][Src] = INF;

	for (int i{ 0 }; i < N; ++i)
	{
		if (Edges[Src][i + 1] == INF)
			continue;

		if ((CurBit & (1 << i)) == (1 << i))
			continue;

		int NewBit{ CurBit | (1 << i) };

		DfsDist[CurBit][Src] = min(DfsDist[CurBit][Src], max(Edges[Src][i + 1], Dfs(NewBit, i + 1)));
	}

	return DfsDist[CurBit][Src];
}

void Solve()
{
	int Result{ Dfs(1,1) };

	if (Result == INF)
		cout << -1;
	else
		cout << Result << endl;

	if (Result != INF)
	{
		int cursor{ 1 };
		int curBit{ 1 };

		while (true)
		{
			cout << cursor << ' ';

			if (curBit == ResultBit)
				break;

			for (int i{ 0 }; i < N; ++i)
			{
				if (Edges[cursor][i + 1] == INF)
					continue;

				if ((curBit & (1 << i)) == (1 << i))
					continue;

				int newBit{ curBit | (1 << i) };

				int result{ max(Edges[cursor][i + 1],DfsDist[newBit][i + 1]) };

				if (result == DfsDist[curBit][cursor])
				{
					cursor = i + 1;
					curBit = newBit;
					break;
				}
			}
		}
	}
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