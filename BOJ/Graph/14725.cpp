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
#define INF numeric_limits<int>::max()
#define MAX 15*1'001

int N;
vector<map<string, int>> Edges(MAX, map<string, int>());

void Input()
{
	cin >> N;
	int Cnt = 1;

	for (int i = 0; i < N; ++i)
	{
		int Num;
		cin >> Num;

		int Cur = 0; // 루트부터 시작

		for (int j = 0; j < Num; ++j)
		{
			string Str;
			cin >> Str;

			if (Edges[Cur].find(Str) == Edges[Cur].end())
			{
				Edges[Cur][Str] = ++Cnt;
			}

			Cur = Edges[Cur][Str]; // 다음 부모로 이동
		}
	}
}

void Dfs(int Src, int Level)
{
	for (const auto& Edge : Edges[Src])
	{
		auto [Str, Dst] {Edge};

		for (int i{ 0 }; i < Level; ++i)
		{
			cout << "--";
		}

		cout << Str << endl;
		Dfs(Dst, 1 + Level);
	}
}

void Solve()
{
	Dfs(0, 0);
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