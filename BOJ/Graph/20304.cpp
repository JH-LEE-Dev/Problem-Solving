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
using State = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'000'001

int N, M;
vector<int> Numbers;
vector<bool> Visited(MAX, false);
int Result;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int Num;
		cin >> Num;

		Numbers.push_back(Num);
	}
}

void Bfs()
{
	queue<State> Q;

	for (int i{ 0 }; i < M; ++i)
	{
		Visited[Numbers[i]] = true;
		Q.push({ Numbers[i],0 });
	}

	int BitLimit{ (int)ceil(log2(N)) };

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto [Src, CurDist] {Cur};

		Result = max(Result, CurDist);

		for (int i{ 0 }; i < BitLimit; ++i)
		{
			int NewDist{ CurDist + 1 };
			int Dst{ Src ^ (1 << i) };

			if (Dst == Src || Dst > N)
				continue;

			if (Visited[Dst] == false)
			{
				Visited[Dst] = true;
				Q.push({ Dst,NewDist });
			}
		}
	}
}

void Solve()
{
	Bfs();

	cout << Result;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();;

	return 0;
}