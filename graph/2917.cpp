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

int N{ 0 }, M{ 0 };
vector<vector<char>> table(MAX, vector<char>(MAX, '.'));
vector<vector<int>> dist(MAX, vector<int>(MAX, -1));
vector<vector<int>> dist_fromWoods(MAX, vector<int>(MAX, INF));

pair<int, int> start;
pair<int, int> goal;
vector<pair<int, int>> woods;

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0)
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

			if (table[i][j] == 'V')
			{
				start.first = i;
				start.second = j;
			}

			if (table[i][j] == 'J')
			{
				goal.first = i;
				goal.second = j;
			}

			if (table[i][j] == '+')
			{
				woods.push_back({ i,j });
			}
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, less<vertex>>pq;
	dist[start.first][start.second] = dist_fromWoods[start.first][start.second];
	pq.push({ dist_fromWoods[start.first][start.second] ,start.first,start.second });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto row{ get<1>(cur) };
		auto col{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[row][col] > curDist)
			continue;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ row + dir_row[i] };
			auto nC{ col + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			auto newDist{ dist_fromWoods[nR][nC] };

			newDist = min(curDist, newDist);

			if (dist[nR][nC] < newDist)
			{
				dist[nR][nC] = newDist;
				pq.push({ newDist,nR,nC });
			}
		}
	}
}

void bfs()
{
	queue<vertex> q;

	for (int i{ 0 }; i < woods.size(); ++i)
	{
		auto row{ woods[i].first };
		auto col{ woods[i].second };

		dist_fromWoods[row][col] = 0;
		q.push({ 0,row,col });
	}

	while (q.empty() == false)
	{
		auto cur{ q.front() };
		q.pop();

		auto row{ get<1>(cur) };
		auto col{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist_fromWoods[row][col] < curDist)
			continue;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ row + dir_row[i] };
			auto nC{ col + dir_col[i] };
			auto newDist{ curDist + 1 };

			if (isValid(nR, nC) == false)
				continue;

			if (table[nR][nC] == '+')
				continue;

			if (dist_fromWoods[nR][nC] > newDist)
			{
				dist_fromWoods[nR][nC] = newDist;
				q.push({ newDist,nR,nC });
			}
		}
	}
}

void solve()
{
	bfs();
	dijkstra();

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