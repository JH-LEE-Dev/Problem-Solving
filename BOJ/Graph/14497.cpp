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
#define MAX 301

int N{ 0 }, M{ 0 };
vector<vector<char>> table(MAX, vector<char>(MAX, '0'));
pair<int, int> start;
pair<int, int> goal;

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= M || col < 0)
		return false;
	else
		return true;
}

void input()
{
	cin >> N >> M;

	cin >> start.first >> start.second >> goal.first >> goal.second;

	start.first -= 1;
	start.second -= 1;
	goal.first -= 1;
	goal.second -= 1;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];
		}
	}
}

void bfs()
{
	deque<vertex> dq;
	dq.push_front({ start.first,start.second,0 });
	dist[start.first][start.second] = 0;

	while (dq.empty() == false)
	{
		auto cur{ dq.front() };
		dq.pop_front();

		auto row{ get<0>(cur) };
		auto col{ get<1>(cur) };
		auto curDist{ get<2>(cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ row + dir_row[i] };
			auto nC{ col + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			if (table[nR][nC] == '1')
			{
				if (dist[nR][nC] > curDist + 1)
				{
					dist[nR][nC] = curDist + 1;
					dq.push_back({ nR,nC,curDist + 1 });
				}
			}
			else
			{
				if (dist[nR][nC] > curDist)
				{
					dist[nR][nC] = curDist;
					dq.push_front({ nR,nC,curDist });
				}
			}
		}
	}
}

void solve()
{
	bfs();

	cout << dist[goal.first][goal.second] + 1;
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