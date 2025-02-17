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
#define MAX 101

int N{ 0 }, T{ 0 };
vector<vector<int>> edges(MAX, vector<int>());
vector<vector<int>> dist(MAX, vector<int>(21, INF));

int result{ INF };

void input()
{
	cin >> N >> T;

	for (int i{ 0 }; i < N; ++i)
	{
		int cnt{ 0 };
		cin >> cnt;

		for (int j{ 0 }; j < cnt; ++j)
		{
			int height{ 0 };
			cin >> height;

			edges[i].push_back(height);
		}
	}
}

void bfs()
{
	deque<vertex> dq;
	dq.push_front({ 0,0,1 });
	dist[0][1] = 0;

	while (dq.empty() == false)
	{
		auto cur{ dq.front() };
		dq.pop_front();

		auto src{ get<1>(cur) };
		auto curH{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src][curH] < curDist)
			continue;

		if (src == N)
		{
			result = min(result, curDist);
			continue;
		}

		for (auto& h : edges[src])
		{
			auto dst{ src + 1 };
			auto newDist{ curDist };

			if ((h - curH == 1) || (curH - h == 1) || (curH == h))
			{
				if (dist[dst][h] > newDist)
				{
					dist[dst][h] = newDist;
					dq.push_front({ newDist,dst,h });
				}
			}
			else if (curH * 2 == h || (curH >= 10 && h == 20))
			{
				if (dist[dst][h] > newDist)
				{
					dist[dst][h] = newDist;
					dq.push_front({ newDist,dst,h });
				}
			}
			else
			{
				auto tempDist = newDist + 1;

				if (tempDist > T)
					continue;

				if (dist[dst][h] > tempDist)
				{
					dist[dst][h] = tempDist;
					dq.push_back({ tempDist,dst,h });
				}
			}
		}
	}
}

void solve()
{
	bfs();

	if (result == INF)
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