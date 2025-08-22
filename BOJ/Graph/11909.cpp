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
using ll = long long;
using vertex = tuple<ll, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 2'223

int N{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, INF));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<int> dir_row{ 0,1 };
vector<int> dir_col{ 1,0 };

void input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			cin >> table[i][j];
		}
	}
}

bool isValid(int r, int c)
{
	if (r > N || r <= 0 || c > N || c <= 0)
		return false;
	else
		return true;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,1,1 });
	dist[1][1] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto curDist{ get<0>(cur) };
		auto row{ get<1>(cur) };
		auto col{ get<2>(cur) };

		if (dist[row][col] < curDist)
			continue;

		for (int i{ 0 }; i < 2; ++i)
		{
			auto nR{ row + dir_row[i] };
			auto nC{ col + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			if (table[row][col] > table[nR][nC])
			{
				if (dist[nR][nC] > curDist)
				{
					dist[nR][nC] = curDist;
					pq.push({ curDist,nR,nC });
				}
			}
			else
			{
				auto w{ table[nR][nC] + 1 - table[row][col] };
				auto newDist{ curDist + w };

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

	cout << dist[N][N];
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