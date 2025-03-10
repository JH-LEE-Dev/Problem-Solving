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

int N, M;
vector<vector<char>> table(MAX, vector<char>(MAX, 0));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

pair<int, int> S;
pair<int, int> E;

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ -1,1,0,0 };

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0)
		return false;
	else
		return true;
}

pair<int, int> slide(int r, int c, pair<int, int> dir, int& weight)
{
	pair<int, int> temp = make_pair(r, c);

	while (true)
	{
		//주어진 방향으로 전진한다.
		temp.first += dir.first;
		temp.second += dir.second;

		//낭떠러지이거나, 구멍이라면, 못 미끄러지므로 그냥 false 느낌의 (-1,-1) 리턴.
		if (isValid(temp.first, temp.second) == false || table[temp.first][temp.second] == 'H')
			return make_pair(-1, -1);

		//미끄러진 결과가 돌이라면, 돌 이전 좌표를 반환
		if (table[temp.first][temp.second] == 'R')
		{
			temp.first -= dir.first;
			temp.second -= dir.second;

			return temp;
		}

		//미끄러진 결과가 도착지라면, 도착지를 반환
		if (table[temp.first][temp.second] == 'E')
		{
			return temp;
		}

		//미끄러지면서 거리 누적
		weight += table[temp.first][temp.second] - '0';
	}
}

void input()
{
	cin >> N >> M;

	swap(N, M);

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == 'T')
			{
				S.first = i;
				S.second = j;
			}

			if (table[i][j] == 'E')
			{
				E.first = i;
				E.second = j;
			}
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,S.first,S.second });
	dist[S.first][S.second] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[r][c] < curDist)
			continue;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			//현재 방향의 바로 다음 좌표가 낭떠러지거나, 구멍이거나, 돌이면 못미끄러지므로 continue
			if (isValid(nR, nC) == false || table[nR][nC] == 'H' || table[nR][nC] == 'R')
				continue;

			//가중치 계산
			auto w{ table[nR][nC] - '0' };

			//미끄러진 결과 좌표 저장할 pair
			pair<int, int> nxt{ nR,nC };

			//만약 바로 다음 좌표가 도착지라면, w = 0이고 미끄러질 필요 없다.
			if (table[nR][nC] == 'E')
				w = 0;
			else
				nxt = slide(nR, nC, make_pair(dir_row[i], dir_col[i]), w);

			//못미끄러지는 경로라면 continue
			if (nxt.first == -1 && nxt.second == -1)
				continue;

			auto newDist{ curDist + w };

			if (dist[nxt.first][nxt.second] > newDist)
			{
				pq.push({ newDist,nxt.first,nxt.second });
				dist[nxt.first][nxt.second] = newDist;
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (dist[E.first][E.second] == INF)
		cout << -1;
	else
		cout << dist[E.first][E.second];
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