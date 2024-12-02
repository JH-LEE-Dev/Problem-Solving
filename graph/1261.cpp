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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 101
vector<vector<char>> table(MAX, vector<char>(MAX, '0'));
int N{ 0 }, M{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
int result{ -1 };

vector<int> dir_x{ 0,0,1,-1 };
vector<int> dir_y{ 1,-1,0,0 };

void dijkstra()
{
	queue<pair<int, int>> myQ;
	myQ.push({ 0,0 });
	dist[0][0] = 0;

	while (myQ.empty() == false)
	{
		auto cur = myQ.front();
		myQ.pop();

		auto curCoord = cur;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto next_x = curCoord.first + dir_x[i];
			auto next_y = curCoord.second + dir_y[i];

			if (next_x >= N || next_x < 0 || next_y >= M || next_y < 0)
				continue;

			if (table[next_x][next_y] == '0')
			{
				if (dist[next_x][next_y] > dist[curCoord.first][curCoord.second])
				{
					myQ.push({ next_x,next_y });
					dist[next_x][next_y] = dist[curCoord.first][curCoord.second];
				}
			}
			else
			{
				if (dist[next_x][next_y] > dist[curCoord.first][curCoord.second] + 1)
				{
					myQ.push({ next_x,next_y });
					dist[next_x][next_y] = dist[curCoord.first][curCoord.second] + 1;
				}
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;
	swap(N, M);

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];
		}
	}

	dijkstra();

	cout << dist[N - 1][M - 1];

	return 0;
}