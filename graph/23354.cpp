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

/*
*	문제 해결 전략
*	1. 출발 지점, 탈영병이 존재하는 곳에서 다익스트라를 실행하고 외판원 순회 알고리즘으로 최소 비용을 구한다.
*/

using namespace std;
using vertex = tuple<int, int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()/2
#define MAX 1'001

vector<vector<int>> table(MAX, vector<int>(MAX, INF));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(6, INF)));
int N;
pair<int, int> start;
vector<pair<int, int>> toCatch;

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

vector<vector<int>> resultDist(6, vector<int>((1 << 5), -1));
int cnt;

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= N || c < 0)
		return false;
	else
		return true;
}

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == -1)
			{
				start.first = i;
				start.second = j;
			}

			if (table[i][j] == 0)
			{
				pair<int, int> temp;
				temp.first = i;
				temp.second = j;

				++cnt;
				toCatch.push_back(temp);
			}
		}
	}

	toCatch.push_back(start);
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	for (int i{ 0 }; i < toCatch.size(); ++i)
	{
		pq.push({ 0,toCatch[i].first,toCatch[i].second,i });
		dist[toCatch[i].first][toCatch[i].second][i] = 0;
	}

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };
		auto curType{ get<3>(cur) };

		if (dist[r][c][curType] < curDist)
			continue;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			auto w{ table[nR][nC] };

			if (w == -1)
				w = 0;

			auto newDist{ curDist + w };

			if (dist[nR][nC][curType] > newDist)
			{
				dist[nR][nC][curType] = newDist;
				pq.push({ newDist,nR,nC,curType });
			}
		}
	}
}

int dfs(int v, int cur)
{
	if (cur == (1 << cnt) - 1)
	{
		if (dist[start.first][start.second][v] == INF)
			return INF;
		else
			return dist[start.first][start.second][v];
	}

	if (resultDist[v][cur] == -1)
		resultDist[v][cur] = INF;
	else
		return resultDist[v][cur];

	for (int i{ 0 }; i < toCatch.size() - 1; ++i)
	{
		if ((1 << i) == (cur & (1 << i)))
			continue;

		auto newBit{ cur | (1 << i) };
		auto dst{ toCatch[i] };

		resultDist[v][cur] = min(resultDist[v][cur], dist[dst.first][dst.second][v] + dfs(i, newBit));
	}

	return resultDist[v][cur];
}

void solve()
{
	dijkstra();

	cout << dfs(toCatch.size() - 1, 0);
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