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
using ll = long long;
using vertex = tuple<ll, int, int, int>;

#define MAX 101
#define endl '\n'
#define INF numeric_limits<ll>::max()

ll N{ 0 }, T{ 0 };
vector<vector<ll>> table(MAX, vector<ll>(MAX, 0));
vector<vector<vector<ll>>> dist(MAX, vector<vector<ll>>(MAX, vector<ll>(3, INF)));
vector<ll> dir_row{ 0,0,1,-1 };
vector<ll> dir_col{ 1,-1,0,0 };
ll result{ 0 };

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= N || col < 0)
		return false;
	else
		return true;
}

void input()
{
	cin >> N >> T;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> table[i][j];
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,0,0,0 });
	dist[0][0][0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto row{ get<1>(cur) };
		auto col{ get<2>(cur) };
		auto cnt{ get<3>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[row][col][cnt] < curDist)
			continue;

		if (row == N - 1 && col == N - 1)
		{
			result = curDist;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ row + dir_row[i] };
			auto nC{ col + dir_col[i] };
			auto nxtCnt{ cnt };

			if (isValid(nR, nC) == false)
				continue;

			++nxtCnt;

			auto newDist{ curDist + T };

			if (nxtCnt == 3)
			{
				nxtCnt = 0;

				newDist += table[nR][nC];

				if (dist[nR][nC][nxtCnt] > newDist)
				{
					dist[nR][nC][nxtCnt] = newDist;
					pq.push({ newDist,nR,nC,nxtCnt });
				}
			}
			else
			{
				if (dist[nR][nC][nxtCnt] > newDist)
				{
					dist[nR][nC][nxtCnt] = newDist;
					pq.push({ newDist,nR,nC,nxtCnt });
				}
			}
		}
	}
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