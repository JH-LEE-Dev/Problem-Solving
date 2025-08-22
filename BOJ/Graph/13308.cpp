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

int N{ 0 }, M{ 0 };
#define MAX 2'505

vector<int> price(MAX, 0);
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<long long>> dist(MAX, vector<long long>(MAX, INF));
long long lowPrice{ INF };

void dijkstra()
{
	priority_queue<tuple<long long, long long, long long>, vector<tuple<long long, long long, long long>>, greater<tuple<long long, long long, long long>>> myPQ;
	myPQ.push({ 0,1,price[1] });
	dist[price[1]][1] = 0;

	while (myPQ.empty() == false)
	{
		auto cur = myPQ.top();
		myPQ.pop();
		auto curVertex = get<1>(cur);
		auto curDist = get<0>(cur);
		auto curPrice = get<2>(cur);

		if (dist[curPrice][curVertex] < curDist)
			continue;

		if (curVertex == N)
		{
			lowPrice = curDist;
			break;
		}

		for (auto& edge : edges[curVertex])
		{
			auto dst = edge.first;
			auto weight = edge.second;
			auto newDist = curDist + (long long)weight * curPrice;

			auto minPrice = min(curPrice, (long long)price[dst]);

			if (dist[minPrice][dst] > newDist)
			{
				dist[minPrice][dst] = newDist;

				myPQ.push({ newDist,dst,minPrice });
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	for (int i{ 1 }; i <= N; ++i)
	{
		cin >> price[i];
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	dijkstra();

	cout << lowPrice;

	return 0;
}