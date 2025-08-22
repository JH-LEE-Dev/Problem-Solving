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
using vertex = tuple<int, int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N, M;
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(3, INF)));
//오른,왼,아래,위
vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

pair<int, int> start;
pair<int, int> goal;

int result{ 0 };

void input()
{
	cin >> N >> M;
	cin >> start.first >> start.second;
	cin >> goal.first >> goal.second;

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

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0 || (table[r][c] == -1))
		return false;
	else
		return true;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,1,start.first,start.second });
	dist[start.first][start.second][1] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<2>(cur) };
		auto c{ get<3>(cur) };
		auto curDist{ get<0>(cur) };
		auto curType{ get<1>(cur) };

		if (dist[r][c][curType] < curDist)
			continue;

		if (r == goal.first && c == goal.second)
		{
			result = curDist;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			auto newDist{ curDist + table[nR][nC] };

			switch (curType % 3)
			{
			case 1:
				if (i < 2)
					continue;
				break;
			case 2:
				if (i >= 2)
					continue;
				break;
			}

			auto newType{ (curType + 1) % 3 };

			if (dist[nR][nC][newType] > newDist)
			{
				dist[nR][nC][newType] = newDist;
				pq.push({ newDist,newType,nR,nC });
			}
		}
	}

	result = -1;
}

void solve()
{
	dijkstra();
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