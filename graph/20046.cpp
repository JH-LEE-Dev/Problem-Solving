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
#define MAX 1'001

int N{ 0 }, M{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];
		}
	}
}

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= M || col < 0)
		return false;
	else
		return true;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ table[0][0],0,0 });
	dist[0][0] = table[0][0];

	if (table[0][0] == -1)
		return;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto row{ get<1>(cur) };
		auto col{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[row][col] < curDist)
			continue;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ row + dir_row[i] };
			auto nC{ col + dir_col[i] };

			if (isValid(nR, nC) == false || table[nR][nC] == -1)
				continue;

			auto newDist{ curDist + table[nR][nC] };

			if (table[nR][nC] == 0)
				newDist = curDist;

			if (dist[nR][nC] > newDist)
			{
				dist[nR][nC] = newDist;
				pq.push({ newDist,nR,nC });
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (dist[N - 1][M - 1] == INF)
		cout << -1;
	else
		cout << dist[N - 1][M - 1];
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