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
using Vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<LL>::max()
#define MAX 1'001

int N, M;
vector<vector<LL>> Table(MAX, vector<LL>(MAX, INF));
vector<vector<bool>> Visited;

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };
LL Result{ INF };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0)
		return false;
	else
		return true;
}

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

bool Bfs(LL Diff)
{
	Visited = vector<vector<bool>>(MAX, vector<bool>(MAX, false));

	queue<Vertex> Q;
	Visited[0][0] = true;
	Q.push({ 0,0,Table[0][0] });

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<0>(Cur) };
		auto C{ get<1>(Cur) };
		auto H{ get<2>(Cur) };

		if (R == N - 1 && C == M - 1)
			return true;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false || Visited[NewR][NewC] == true)
				continue;

			if (Table[NewR][NewC] - H > Diff)
				continue;

			Visited[NewR][NewC] = true;
			Q.push({ NewR,NewC,Table[NewR][NewC] });
		}
	}

	return false;
}

void Bsearch()
{
	LL Left{ 0 };
	LL Right{ 1'000'000'000 };

	while (Left <= Right)
	{
		LL Middle{ (Left + Right) / 2 };

		if (Bfs(Middle) == false)
			Left = Middle + 1;
		else
		{
			Right = Middle - 1;

			Result = min(Result, Middle);
		}
	}
}

void Solve()
{
	Bsearch();

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