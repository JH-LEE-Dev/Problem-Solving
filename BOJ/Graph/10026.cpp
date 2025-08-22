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

/*
*	문제 이해
*	1. 적록 색약이 보는 그림에서, R,G는 같은 소속이다.
*
*	문제 해결 전략
*	1. 적록 색약이 볼 때는,R,G를 동일 취급하여 BFS를 실행하고, 아닌 사람이 볼 때는 다르게 취급하여 BFS를 실행.
*	2. BFS로 구분된 영역의 개수를 비교.
*/
using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N;
vector<vector<char>> table(MAX, vector<char>(MAX));
vector<vector<int>> dist_RG(MAX, vector<int>(MAX, INF));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> table[i][j];
		}
	}
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= N || c < 0)
		return false;
	else
		return true;
}

void bfs(int r, int c, char type, bool disabled)
{
	queue<tuple<int, int, int>> q;
	q.push({ 0, r,c });

	if (disabled == false)
		dist[r][c] = 0;
	else
		dist_RG[r][c] = 0;

	while (q.empty() == false)
	{
		auto cur{ q.front() };
		q.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };
			auto newDist{ curDist + 1 };

			if (disabled == false)
			{
				if (isValid(nR, nC) == false || table[nR][nC] != type)
					continue;
			}
			else
			{
				if (isValid(nR, nC) == false)
					continue;

				if (type == 'B' && type != table[nR][nC])
					continue;

				if ((type == 'R' || type == 'G') && table[nR][nC] == 'B')
					continue;
			}

			if (disabled == false)
			{
				if (dist[nR][nC] == INF)
				{
					dist[nR][nC] = newDist;
					q.push({ newDist,nR,nC });
				}
			}
			else
			{
				if (dist_RG[nR][nC] == INF)
				{
					dist_RG[nR][nC] = newDist;
					q.push({ newDist,nR,nC });
				}
			}
		}
	}
}

void solve()
{
	int normal{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			if (dist[i][j] == INF)
			{
				bfs(i, j, table[i][j], false);
				++normal;
			}
		}
	}

	int disabled{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			if (dist_RG[i][j] == INF)
			{
				bfs(i, j, table[i][j], true);
				++disabled;
			}
		}
	}

	cout << normal << ' ' << disabled;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}