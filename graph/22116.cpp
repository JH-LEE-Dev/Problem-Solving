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
using vertex = tuple<ll, int, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 1'001

int N{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
vector<vector<ll>> dist(MAX, vector<ll>(MAX, INF));
vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> table[i][j];
		}
	}
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= N || c < 0)
		return false;
	else
		return true;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0,0 });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto row{ get<1>(cur) };
		auto col{ get<2>(cur) };
		auto curMax{ get<0>(cur) };

		if (dist[row][col] < curMax)
			continue;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ row + dir_row[i] };
			auto nC{ col + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			ll newMax{ max(curMax, abs((ll)table[nR][nC] - (ll)table[row][col])) };

			if (dist[nR][nC] > newMax)
			{
				dist[nR][nC] = newMax;
				pq.push({ newMax,nR,nC });
			}
		}
	}
}

void solve()
{
	if (N == 1)
	{
		cout << 0;
		return;
	}

	dijkstra();

	cout << dist[N - 1][N - 1];
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