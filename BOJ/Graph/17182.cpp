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

#define MAX 11
#define endl '\n'
#define INF numeric_limits<int>::max()

int N{ 0 }, K{ 0 };
vector<vector<int>> edges(MAX, vector<int>(MAX, INF));
pair<int, int> start{ -1,0 };
vector<vector<int>> dist(MAX, vector<int>((1 << MAX), INF));

int result_state{ -1 }, result{ INF };

void input()
{
	cin >> N >> K;

	start.first = K;
	result_state = (1 << N) - 1;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> edges[i][j];
		}
	}
}

void dijkstra()
{
	dist[K][(1 << K)] = 0;
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,K,(1 << K) });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto state{ get<2>(cur) };

		if (dist[src][state] < curDist)
			continue;

		if (state == result_state)
		{
			result = curDist;

			break;
		}

		for (int i{ 0 }; i < N; ++i)
		{
			if (src == i)
				continue;

			auto newDist{ curDist + edges[src][i] };
			auto newState{ state | (1 << i) };

			if (dist[i][newState] > newDist)
			{
				dist[i][newState] = newDist;
				pq.push({ newDist,i,newState });
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