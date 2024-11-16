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

#define endl '\n'
#define INF numeric_limits<long long>::max()
using namespace std;
#define MAX 100'005

int N{ 0 }, M{ 0 }, K{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> interview;
vector<long long> dist(MAX, INF);

int minVertex{ -1 };
long long result{ -1 };

void dijkstra(int start)
{
	dist[start] = 0;
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> myPQ;
	myPQ.push({ 0,start });

	while (myPQ.empty() == false)
	{
		auto cur = myPQ.top();
		myPQ.pop();

		auto curVertex = cur.second;
		auto curDist = cur.first;

		if (curDist > dist[curVertex])
		{
			continue;
		}

		for (auto& edge : edges[curVertex])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (newDist < dist[dst])
			{
				dist[dst] = newDist;
				myPQ.push({ newDist,dst });
			}
		}
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
		edges[dst].push_back({ src,w });
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int input{ 0 };
		cin >> input;
		interview.push_back(input);
	}

	for (int i{ 0 }; i < K; ++i)
	{
		dijkstra(interview[i]);
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		if (dist[i] > result)
		{
			result = dist[i];
			minVertex = i;
		}
	}

	cout << minVertex << endl;
	cout << result;

	return 0;
}