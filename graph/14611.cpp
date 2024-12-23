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

using ll = long long;

#define endl '\n'
#define INF numeric_limits<ll>::max()
using namespace std;

#define MAX 301



vector<vector<ll>> weight(MAX, vector<ll>(MAX, INF));
vector<vector<ll>> dist(MAX, vector<ll>(MAX, INF));
int N{ 0 }, M{ 0 };

vector<int> dir_row{ 0,0,1,-1,1,1,-1,-1 };
vector<int> dir_col{ 1,-1,0,0,1,-1,-1,1 };
ll result{ INF };

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= M || col < 0 || weight[row][col] == INF)
		return false;
	else
		return true;
}

void dijkstra()
{
	priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> myPQ;

	for (int i{ 1 }; i < M; ++i)
	{
		if (weight[0][i] == INF)
			continue;

		myPQ.push({ weight[0][i],0,i });
		dist[0][i] = weight[0][i];
	}

	for (int i{ 1 }; i < N; ++i)
	{
		if (weight[i][M - 1] == INF)
			continue;

		myPQ.push({ weight[i][M - 1],i,M - 1 });
		dist[i][M - 1] = weight[i][M - 1];
	}

	while (myPQ.empty() == false)
	{
		auto cur{ myPQ.top() };
		myPQ.pop();

		auto curDist{ get<0>(cur) };
		auto src_row{ get<1>(cur) };
		auto src_col{ get<2>(cur) };

		if (dist[src_row][src_col] < curDist)
			continue;

		for (int i{ 0 }; i < 8; ++i)
		{
			auto new_row{ src_row + dir_row[i] };
			auto new_col{ src_col + dir_col[i] };

			if (isValid(new_row, new_col))
			{
				auto newDist{ curDist + weight[new_row][new_col] };

				if (dist[new_row][new_col] > newDist)
				{
					dist[new_row][new_col] = newDist;
					myPQ.push({ newDist,new_row,new_col });
				}
			}
		}
	}

	for (int i{ 1 }; i < N; ++i)
	{
		result = min(dist[i][0], result);
	}

	for (int i{ 1 }; i < M; ++i)
	{
		result = min(dist[N - 1][i], result);
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
			cin >> weight[i][j];

			if (weight[i][j] == -1)
				weight[i][j] = INF;
			else if (weight[i][j] == -2)
				weight[i][j] = 0;
		}
	}

	dijkstra();

	if (result != INF)
		cout << result;
	else
		cout << -1;

	return 0;
}