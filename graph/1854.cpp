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
#define INF numeric_limits<int>::max()
using namespace std;
#define MAX 1'005

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<priority_queue<int>> nthDist(MAX, priority_queue<int>());
int N{ 0 }, M{ 0 }, K{ 0 };

void dijkstra()
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> myPQ;
	myPQ.push({ 0,1 });
	nthDist[1].push(0);

	while (myPQ.empty() == false)
	{
		auto cur = myPQ.top();
		myPQ.pop();

		auto curVertex = cur.second;
		auto curDist = cur.first;

		for (auto& edge : edges[curVertex])
		{
			auto dst = edge.first;
			auto weight = edge.second;
			auto newDist = curDist + weight;

			if (nthDist[dst].size() < K)
			{
				nthDist[dst].push(newDist);
				myPQ.push({ newDist,dst });
			}
			else
			{
				if (nthDist[dst].top() > newDist)
				{
					myPQ.push({ newDist,dst });
					nthDist[dst].pop();
					nthDist[dst].push(newDist);
				}
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

		edges[src].push_back({ dst,w });
	}

	dijkstra();

	for (int i{ 1 }; i <= N; ++i)
	{
		if (nthDist[i].size() < K)
			cout << -1 << endl;
		else
			cout << nthDist[i].top() << endl;
	}

	return 0;
}