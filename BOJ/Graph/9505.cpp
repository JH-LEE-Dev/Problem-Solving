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
*	1. 무력화 시간을 저장하기 위해서 map 자료 구조를 사용한다.
*	2. 주어진 2차원 table에서 table의 가장 자리로 이동할 수 있는 가장 최소 비용을 구한다.
*/

using namespace std;
using ll = long long;
using vertex = tuple<ll, int, int>;
#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 1'001

int T;
int K, W, H;

vector<vector<char>> table(MAX, vector<char>(MAX));
pair<int, int> s;
vector<vector<ll>> dist(MAX, vector<ll>(MAX, INF));
map<char, int> weight;

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

void input()
{
	table = vector<vector<char>>(MAX, vector<char>(MAX));
	dist = vector<vector<ll>>(MAX, vector<ll>(MAX, INF));
	weight.clear();

	cin >> K >> W >> H;

	swap(W, H);

	for (int i{ 0 }; i < K; ++i)
	{
		char ship;
		int w;

		cin >> ship >> w;

		weight[ship] = w;
	}

	for (int i{ 0 }; i < W; ++i)
	{
		for (int j{ 0 }; j < H; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == 'E')
			{
				s.first = i;
				s.second = j;
			}
		}
	}
}

bool isValid(int r, int c)
{
	if (r >= W || r < 0 || c >= H || c < 0)
		return false;
	else
		return true;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	dist[s.first][s.second] = 0;
	pq.push({ 0,s.first,s.second });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[r][c] < curDist)
			continue;

		if (r >= W - 1 || r <= 0 || c >= H - 1 || c <= 0)
		{
			cout << curDist << endl;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			auto w{ weight[table[nR][nC]] };
			auto newDist{ curDist + w };

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
	cin >> T;

	while (T != 0)
	{
		input();

		dijkstra();

		--T;
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