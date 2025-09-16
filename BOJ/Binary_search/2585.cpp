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

int N, K;
vector<tuple<int, int, int>> Vertexes;
int MAX;

void Input()
{
	cin >> N >> K;

	MAX = (int)ceil(hypot(10'000, 10'000) / 10);

	Vertexes.push_back({ 0,0,0 });

	for (int i{ 0 }; i < N; ++i)
	{
		int X, Y;
		cin >> X >> Y;

		Vertexes.push_back({ i + 1,X,Y });
	}

	Vertexes.push_back({ N + 1,10'000,10'000 });
}

bool Bfs(int Limit)
{
	Limit *= 10;

	vector<int> Visited(N + 5, INF);
	queue<tuple<int, double, int, int, int>> Q;
	Q.push({ 0,Limit,0,0,0 });
	Visited[0] = 0;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto [CurCnt, CurFuel, Id, X, Y] {Cur};

		if (Id == N + 1)
			return true;

		for (int i{ 0 }; i <= N + 1; ++i)
		{
			if (i == Id)
				continue;

			auto [NewId, X1, Y1] {Vertexes[i]};
			auto NewCnt{ CurCnt };
			auto NewFuel{ CurFuel };
			double Dist{ hypot(abs(X - X1),abs(Y - Y1)) };

			if (Dist > Limit)
				continue;

			if (NewFuel - Dist < 0)
			{
				if (NewCnt == K)
					continue;

				NewFuel = Limit;
				++NewCnt;
			}

			NewFuel -= Dist;

			if (Visited[i] > NewCnt)
			{
				Q.push({ NewCnt,NewFuel,i,X1,Y1 });
				Visited[i] = NewCnt;
			}
		}
	}

	return false;
}

void Bsearch()
{
	int Left{ 0 };
	int Right{ MAX };

	while (Left <= Right)
	{
		int Middle{ (Left + Right) / 2 };

		if (Bfs(Middle) == false)
			Left = Middle + 1;
		else
			Right = Middle - 1;
	}

	cout << Left;
}

void Solve()
{
	Bsearch();
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