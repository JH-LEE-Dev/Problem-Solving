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
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 501

int H, W;
vector<vector<char>> table(MAX, vector<char>(MAX));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<vector<bool>> adjacent(MAX, vector<bool>(MAX, false));

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

pair<int, int> s;
pair<int, int> e;

bool isValid(int r, int c)
{
	if (r >= H || r < 0 || c >= W || c < 0)
		return false;
	else
		return true;
}

void input()
{
	cin >> H >> W;

	for (int i{ 0 }; i < H; ++i)
	{
		for (int j{ 0 }; j < W; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == 'S')
			{
				s.first = i;
				s.second = j;
			}

			if (table[i][j] == 'E')
			{
				e.first = i;
				e.second = j;
			}

			if (table[i][j] == '#')
			{
				for (int k{ 0 }; k < 4; ++k)
				{
					int r{ i + dir_row[k] };
					int c{ j + dir_col[k] };

					if (isValid(r, c) == false)
						continue;

					adjacent[r][c] = true;
				}
			}
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,s.first,s.second });
	dist[s.first][s.second] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[r][c] < curDist)
			continue;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			auto newDist{ curDist };

			if (table[nR][nC] == '#')
				continue;

			if (adjacent[r][c] == true && adjacent[nR][nC] == true)
			{
				if (dist[nR][nC] > newDist)
				{
					dist[nR][nC] = newDist;
					pq.push({ newDist,nR,nC });
				}
			}
			else
			{
				newDist += 1;

				if (dist[nR][nC] > newDist)
				{
					dist[nR][nC] = newDist;
					pq.push({ newDist,nR,nC });
				}
			}
		}
	}
}

void solve()
{
	dijkstra();

	cout << dist[e.first][e.second];
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