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
using ll = long long;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 6'002

int N;
pair<int, int> start;
pair<int, int> goal;
vector<pair<int, int>> vertexes;
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

void input()
{
	cin >> start.first >> start.second;
	cin >> goal.first >> goal.second;

	cin >> N;

	vertexes.push_back(start);

	for (int i{ 0 }; i < N; ++i)
	{
		int row, col;
		cin >> row >> col;

		vertexes.push_back({ row,col });
	}

	vertexes.push_back(goal);
}

bool primeNumber(int num)
{
	if (num == 0 || num == 1)
		return false;

	for (int i{ 2 }; i * i <= num; ++i)
	{
		if (num % i == 0)
			return false;
	}

	return true;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,start.first,start.second });
	dist[start.first + 3000][start.second + 3000] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto row{ get<1>(cur) };
		auto col{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[row + 3000][col + 3000] < curDist)
			continue;

		for (auto& dst : vertexes)
		{
			if (row == dst.first && col == dst.second)
				continue;

			auto row_dst{ dst.first };
			auto col_dst{ dst.second };

			int dist_int{ (int)hypot(abs(row - row_dst),abs(col - col_dst)) };

			if (primeNumber(dist_int) == false)
				continue;

			auto newDist{ curDist + dist_int };

			if (dist[row_dst + 3000][col_dst + 3000] > newDist)
			{
				dist[row_dst + 3000][col_dst + 3000] = newDist;
				pq.push({ newDist,row_dst,col_dst });
			}
		}
	}
}

void solve()
{
	dijkstra();

	auto result{ dist[goal.first + 3000][goal.second + 3000] };

	if (result == INF || result == 0)
		cout << -1;
	else
		cout << result;
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