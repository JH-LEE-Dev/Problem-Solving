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
using vertex = tuple<double, int, int>;

#define endl '\n'
#define INF numeric_limits<double>::max()
#define MAX 51

int N, K;
vector<vector<pair<int, int>>>edges(MAX, vector<pair<int, int>>());
vector<vector<double>> dist(MAX, vector<double>(MAX, INF));

double result{ 0 };

void input()
{
	cin >> N >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		string temp;
		cin >> temp;

		for (int j{ 0 }; j < N; ++j)
		{
			edges[i].push_back({ j,temp[j] - '0' });
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0,0 });
	dist[0][0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<2>(cur) };
		auto cnt{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src][cnt] < curDist)
			continue;

		if (src == 1)
		{
			result = curDist;
			return;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newCnt{ cnt };

			auto newDist{ curDist + w };

			if (dist[dst][newCnt] > newDist)
			{
				dist[dst][newCnt] = newDist;
				pq.push({ newDist,newCnt,dst });
			}

			if (cnt < K)
			{
				++newCnt;
				newDist = curDist + (double)w * 0.5;

				if (dist[dst][newCnt] > newDist)
				{
					dist[dst][newCnt] = newDist;
					pq.push({ newDist,newCnt,dst });
				}
			}
		}
	}
}

void solve()
{
	dijkstra();

	cout << fixed << setprecision(9) << result;
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