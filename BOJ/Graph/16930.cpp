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
using State = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int N, M, K;
vector<vector<char>> Table(MAX, vector<char>(MAX, '.'));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

pair<int, int> Start;
pair<int, int> End;

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0 || Table[R][C] == '#')
		return false;
	else
		return true;
}

void Input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];
		}
	}

	cin >> Start.first >> Start.second;
	cin >> End.first >> End.second;
}

void Bfs()
{
	queue<State> Q;
	Q.push({ 0,Start.first - 1,Start.second - 1 });
	vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));
	Dist[Start.first - 1][Start.second - 1] = 0;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto [CurDist, R, C] {Cur};

		if (R == End.first - 1 && C == End.second - 1)
		{
			cout << CurDist;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			for (int j{ 1 }; j <= K; ++j)
			{
				auto NewR{ Dir_Row[i] * j + R };
				auto NewC{ Dir_Col[i] * j + C };
				auto NewDist{ CurDist + 1 };

				if (IsValid(NewR, NewC) == false)
					break;

				if (Dist[NewR][NewC] < NewDist)
					break;

				if (Dist[NewR][NewC] > NewDist)
				{
					Dist[NewR][NewC] = NewDist;
					Q.push({ NewDist,NewR,NewC });
				}
				else if (Dist[NewR][NewC] == NewDist)
					continue;
			}
		}
	}

	cout << -1;
}

void Solve()
{
	Bfs();
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