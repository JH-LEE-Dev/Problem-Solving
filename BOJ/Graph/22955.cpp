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
using vertex = tuple<int, int, int, bool>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int N, M;
vector<vector<char>> table(MAX, vector<char>(MAX));
vector<vector<int>> dogs(MAX, vector<int>(MAX, 0));
pair<int, int> start;
pair<int, int> goal;

//¾Æ,À§,¿À,¿Þ
vector<int> dir_row{ 1,-1,0,0 };
vector<int> dir_col{ 0,0,1,-1 };

vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0 || table[r][c] == 'D')
		return false;
	else
		return true;
}

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == 'C')
			{
				start.first = i;
				start.second = j;
			}

			if (table[i][j] == 'E')
			{
				goal.first = i;
				goal.second = j;
			}
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,start.first,start.second,false });
	dist[start.first][start.second] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };
		auto isFalling{ get<3>(cur) };

		if (dist[r][c] < curDist)
			continue;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };
			auto newDist{ curDist };

			if (isValid(nR, nC) == false)
				continue;

			if (i == 0)
			{
				if (isFalling)
				{
					if (table[nR][nC] != 'X')
					{
						newDist += 10;

						if (dist[nR][nC] > newDist)
						{
							dist[nR][nC] = newDist;
							pq.push({ newDist,nR,nC,false });
						}
					}
					else
					{
						if (dist[nR][nC] > newDist)
						{
							dist[nR][nC] = newDist;
							pq.push({ newDist,nR,nC,true });
						}
					}

					break;
				}

				if (table[nR][nC] == 'L')
				{
					if (table[r][c] != 'X')
					{
						newDist += 5;

						if (dist[nR][nC] > newDist)
						{
							dist[nR][nC] = newDist;
							pq.push({ newDist,nR,nC,false });
						}
					}
				}
			}
			else if (i == 1 && isFalling == false)
			{
				if (table[nR][nC] != 'X' && table[r][c] == 'L')
				{
					newDist += 5;

					if (dist[nR][nC] > newDist)
					{
						dist[nR][nC] = newDist;
						pq.push({ newDist,nR,nC,false });
					}
				}
			}
			else if (isFalling == false)
			{
				newDist += 1;

				bool newFalling{ isFalling };

				if (table[nR][nC] == 'X')
					newFalling = true;

				if (dist[nR][nC] > newDist)
				{
					dist[nR][nC] = newDist;
					pq.push({ newDist,nR,nC,newFalling });
				}
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (dist[goal.first][goal.second] == INF)
		cout << "dodo sad";
	else
		cout << dist[goal.first][goal.second];
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