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
using crossRoad = tuple<char, int, int>;
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 21

int N, M;
vector<vector<char>> table(MAX, vector<char>(MAX));
vector<pair<int, int>> crossCoord(MAX);
map<pair<int, int>, tuple<bool, int, int>> crossRoads;
pair<int, int> s;
pair<int, int> e;

// 우좌, 하상
vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

bool input()
{
	table = vector<vector<char>>(MAX, vector<char>(MAX));
	crossCoord.clear();
	crossRoads.clear();

	cin >> N >> M;

	if (N == 0 && M == 0)
		return false;

	int cnt{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == 'A')
			{
				s.first = i;
				s.second = j;

				continue;
			}

			if (table[i][j] == 'B')
			{
				e.first = i;
				e.second = j;

				continue;
			}

			if ((int)table[i][j] >= (int)('0') && (int)table[i][j] <= (int)('9'))
			{
				crossCoord[table[i][j] - '0'] = make_pair(i, j);

				++cnt;
			}
		}
	}

	for (int i{ 0 }; i < cnt; ++i)
	{
		int temp;
		cin >> temp;

		char init;
		cin >> init;

		int a, b;

		cin >> a >> b;

		bool dir{ false };

		if (init == '|')
		{
			//a를 기준으로 생각하기 위해서(a가 초기 신호등의 활성화 시간) '|' 방향일 때는 a와 b를 바꿔준다.
			//즉 '|' 방향의 활성화 시간 b를 a 위치로 보낸다.
			swap(a, b);
			dir = true;
		}

		crossRoads[make_pair(crossCoord[i].first, crossCoord[i].second)] = { dir,a,b };
	}

	return true;
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0 || table[r][c] == '.')
		return false;
	else
		return true;
}

void dijkstra()
{
	dist = vector<vector<int>>(MAX, vector<int>(MAX, INF));

	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,s.first,s.second });
	dist[s.first][s.second] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[r][c] < curDist)
			continue;

		if (r == e.first && c == e.second)
		{
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			auto newDist{ curDist + 1 };

			if ((int)table[nR][nC] >= (int)('0') && (int)table[nR][nC] <= (int)('9'))
			{
				bool dir{ get<0>(crossRoads[make_pair(nR,nC)]) };
				int a{ get<1>(crossRoads[make_pair(nR,nC)]) };
				int b{ get<2>(crossRoads[make_pair(nR,nC)]) };

				// i에 따라서 두 방향으로 나뉘므로 i/2를 해서 bool로 편리하게 방향 체크.
				// 0,1 -> '-' 방향 , 2,3 -> '|' 방향
				bool dirCur{ (int)(i / 2) };

				int remain{ curDist % (a + b) };

				//시작 시간보다 작을 때만 지나갈 수 있다.
				//만약 신호등이 '-'방향으로 1,2초 켜져 있으면 2초에는 이 신호등을 건널 수 없다는 뜻이다. 즉 2초까지 켜져있다는 뜻이다.
				if (remain < a)
				{
					//초기 방향의 활성화 시간 안에 들어왔을 경우,
					//신호등의 초기 방향과 현재 내 방향이 같다면, 그냥 지나가면 되고,
					//방향이 다르다면, 다음 방향이 되기를 기다려야 하므로 활성화 시간 b로 가게 한다.
					if (dirCur != dir)
					{
						newDist += (a - remain);
					}
				}
				else
				{
					//만약 두 번째 방향의 활성화 시간으로 도달했다면, 초기 방향과 내 방향이 같다면, 첫 번째 활성화 시간으로 가야 하므로
					//다음 주기까지 기다린다.
					//만약 초기 방향과 다르다면, 그냥 지나가면 된다.
					if (dirCur == dir)
					{
						newDist += (a + b - remain);
					}
				}
			}

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
	while (true)
	{
		if (input() == false)
			return;

		dijkstra();

		if (dist[e.first][e.second] == INF)
			cout << "impossible" << endl;
		else
			cout << dist[e.first][e.second] << endl;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}