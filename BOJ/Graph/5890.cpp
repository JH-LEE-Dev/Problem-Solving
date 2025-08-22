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
#define MAX 1'001

int N;
pair<int, int> Start;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

void Input()
{
	cin >> N >> Start.first >> Start.second;

	for (int i{ 0 }; i < N; ++i)
	{
		int R, C;
		cin >> R >> C;

		Table[R][C] = 1;
	}
}

bool IsValid(int R, int C)
{
	if (R >= MAX || R < 0 || C >= MAX || C < 0)
		return false;
	else
		return true;
}

int Bfs()
{
	deque<tuple<int, int, int>> Q;
	Q.push_front({ 0,Start.first,Start.second });
	Dist[Start.first][Start.second] = 0;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop_front();

		auto R{ get<1>(Cur) };
		auto C{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				return CurDist;

			if (Dist[NewR][NewC] == INF)
			{
				auto NewDist{ CurDist + Table[NewR][NewC] };
				Dist[NewR][NewC] = NewDist;

				if (Table[NewR][NewC] == 1)
				{
					Q.push_back({ NewDist ,NewR,NewC });
				}
				else
				{
					Q.push_front({ NewDist ,NewR,NewC });
				}
			}
		}
	}

	return -1;
}

void Solve()
{
	cout << Bfs();
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