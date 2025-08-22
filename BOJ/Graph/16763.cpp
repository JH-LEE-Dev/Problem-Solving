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

#define endl '\n'
#define INF numeric_limits<long long>::max()
using namespace std;

#define MAX 50'001

int N{ 0 }, M{ 0 }, K{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
unordered_map<int, int> stopBy;

vector<vector<long long>> dist(MAX, vector<long long>(2, INF));

void dijkstra()
{
	dist[N][0] = 0;
	priority_queue<tuple<long long, int, bool>, vector<tuple<long long, int, bool>>, greater<tuple<long long, int, bool>>> myPQ;
	myPQ.push({ 0,N,false });

	while (myPQ.empty() == false)
	{
		auto cur{ myPQ.top() };
		myPQ.pop();
		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curEat{ get<2>(cur) };

		if (dist[src][curEat] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (curEat == false)
			{
				if (stopBy.find(dst) != stopBy.end())
				{
					if (dist[dst][1] > newDist - stopBy[dst])
					{
						dist[dst][1] = newDist - stopBy[dst];
						myPQ.push({ newDist - stopBy[dst],dst,1 });
					}
				}

				if (dist[dst][curEat] > newDist)
				{
					dist[dst][curEat] = newDist;
					myPQ.push({ newDist,dst,curEat });
				}
			}
			else
			{
				if (dist[dst][curEat] > newDist)
				{
					dist[dst][curEat] = newDist;
					myPQ.push({ newDist,dst,curEat });
				}
			}
		}
	}

	for (int i{ 1 }; i < N; ++i)
	{
		if (dist[i][1] <= dist[i][0])
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M >> K;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int n{ 0 }, w{ 0 };
		cin >> n >> w;

		stopBy[n] = w;
	}

	dijkstra();

	return 0;
}