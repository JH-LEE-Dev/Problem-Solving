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
int N{ 0 }, M{ 0 }, K{ 0 };
#define MAX 105
vector<vector<tuple<int, int, int>>> edges(MAX, vector<tuple<int, int, int>>());
vector<vector<int>> dist(MAX, vector<int>(10'005, INF));

void dijkstra()
{
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> myPQ;
	myPQ.push(make_tuple(0, 1, 0));
	dist[1][0] = 0;

	while (myPQ.empty() == false)
	{
		auto cur = myPQ.top();
		myPQ.pop();

		auto curVertex = get<1>(cur);
		auto curDist = get<0>(cur);
		auto curCost = get<2>(cur);

		if (dist[curVertex][curCost] < curDist)
			continue;

		for (auto& edge : edges[curVertex])
		{
			auto dst = get<0>(edge);
			auto weight = get<1>(edge);
			auto dst_cost = get<2>(edge);
			auto newDist = curDist + weight;
			auto newCost = curCost + dst_cost;

			if (newCost <= M && dist[dst][newCost] > newDist)
			{
				for (int i{ newCost + 1 }; i <= M; ++i)
				{
					if (dist[dst][i] < newDist)
						break;
					dist[dst][i] = newDist;
				}

				dist[dst][newCost] = newDist;

				myPQ.push(make_tuple(newDist, dst, newCost));
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T{ 0 };
	cin >> T;

	while (T != 0)
	{
		cin >> N >> M >> K;

		edges = vector<vector<tuple<int, int, int>>>(MAX, vector<tuple<int, int, int>>());
		dist = vector<vector<int>>(MAX, vector<int>(10'005, INF));

		for (int i{ 0 }; i < K; ++i)
		{
			int src{ 0 }, dst{ 0 }, w{ 0 }, cost{ 0 };
			cin >> src >> dst >> cost >> w;
			edges[src].push_back(make_tuple(dst, w, cost));
		}

		for (int i{ 1 }; i <= N; ++i)
		{
			sort(edges[i].begin(), edges[i].end(), [](const tuple<int, int, int >& lhs, const tuple<int, int, int >& rhs) {
				return get<2>(lhs) < get<2>(rhs);
				});
		}

		dijkstra();
		int result{ INF };
		for (int i{ 0 }; i <= M; ++i)
		{
			result = min(result, dist[N][i]);
		}

		if (result == INF)
			cout << "Poor KCM" << endl;
		else
			cout << result << endl;

		--T;
	}

	return 0;
}