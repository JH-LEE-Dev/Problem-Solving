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
#define MAX 2'001
#define endl '\n'
#define INF numeric_limits<int>::max()

vector<vector<int>> edges(MAX, vector<int>(MAX, -1));
vector<vector<ll>> dist(MAX, vector<ll>(MAX, INF));

int N{ 0 }, M{ 0 };

vector<int> dir_row{ 0,0,1,-1,1,1,-1,-1 };
vector<int> dir_col{ 1,-1,0,0,1,-1,-1,1 };

ll result{ INF };

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= M || col < 0)
		return false;
	else
		return true;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> myPQ;

	for (int i{ 1 }; i < M; ++i)
	{
		if (edges[0][i] == 1)
		{
			myPQ.push({ 0,0,i });
			dist[0][i] = 0;
		}
		else
		{
			myPQ.push({ 1,0,i });
			dist[0][i] = 1;
		}
	}

	for (int i{ 1 }; i < N - 1; ++i)
	{
		if (edges[i][M - 1] == 1)
		{
			myPQ.push({ 0,i,M - 1 });
			dist[i][M - 1] = 0;
		}
		else
		{
			myPQ.push({ 1,i,M - 1 });
			dist[i][M - 1] = 1;
		}
	}

	while (myPQ.empty() == false)
	{
		auto cur{ myPQ.top() };
		myPQ.pop();

		auto row{ get<1>(cur) };
		auto col{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[row][col] < curDist)
			continue;

		for (int i{ 0 }; i < 8; ++i)
		{
			auto dst_row{ row + dir_row[i] };
			auto dst_col{ col + dir_col[i] };
			auto newDist{ curDist };

			if (isValid(dst_row, dst_col) == false)
				continue;

			if (edges[dst_row][dst_col] != 1)
			{
				newDist += 1;
			}

			if (dist[dst_row][dst_col] > newDist)
			{
				dist[dst_row][dst_col] = newDist;
				myPQ.push({ newDist,dst_row,dst_col });
			}
		}
	}

	for (int i{ 1 }; i < N; ++i)
	{
		result = min(result, dist[i][0]);
	}

	for (int i{ 1 }; i < M - 1; ++i)
	{
		result = min(result, dist[N - 1][i]);
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> edges[i][j];
		}
	}

	dijkstra();

	cout << result;

	return 0;
}