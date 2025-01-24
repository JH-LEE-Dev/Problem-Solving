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
using vertex = tuple<int, int, int, bool>;
int N{ 0 }, M{ 0 };

#define MAX 100'001
#define endl '\n'
#define INF numeric_limits<int>::max()

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist_FOX(MAX, INF);
vector<vector<int>> dist_WOLF(MAX, vector<int>(2, INF));

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w * 2 });
		edges[dst].push_back({ src,w * 2 });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,1,0,false });
	pq.push({ 0,1,1,false });
	dist_FOX[1] = 0;
	dist_WOLF[1][false] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curType{ get<2>(cur) };
		auto prevFlash{ get<3>(cur) };

		if (curType == 0)
		{
			if (dist_FOX[src] < curDist)
				continue;
		}
		else
		{
			if (dist_WOLF[src][prevFlash] < curDist)
				continue;
		}


		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };

			if (curType == 1)
			{
				if (prevFlash == true)
				{
					w += w;
				}
				else
				{
					w /= 2;
				}
			}

			auto newDist{ curDist + w };

			if (curType == 0)
			{
				if (dist_FOX[dst] > newDist)
				{
					dist_FOX[dst] = newDist;
					pq.push({ newDist,dst,curType,false });
				}
			}
			else
			{
				if (dist_WOLF[dst][!prevFlash] > newDist)
				{
					dist_WOLF[dst][!prevFlash] = newDist;
					pq.push({ newDist,dst,curType,!prevFlash });
				}
			}
		}
	}
}

void solve()
{
	dijkstra();

	int result{ 0 };

	for (int i{ 1 }; i <= N; ++i)
	{
		auto wolfDist{ min(dist_WOLF[i][0], dist_WOLF[i][1]) };

		if (dist_FOX[i] < wolfDist)
			++result;
	}

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