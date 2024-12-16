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
#define INF numeric_limits<ll>::max()
using namespace std;

using ll = long long;

#define MAX 200'001

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
int N{ 0 }, M{ 0 }, S{ 0 }, E{ 0 };

vector<ll> dist_forward(MAX, INF);
vector<ll> dist_reverse(MAX, INF);
vector<int> parent(MAX, -1);
vector<bool> visited(MAX, false);

ll result{ 0 };

void dijkstra_forward()
{
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> myPQ;
	myPQ.push({ 0,E });
	dist_forward[E] = 0;

	while (myPQ.empty() == false)
	{
		auto cur{ myPQ.top() };
		myPQ.pop();

		auto src{ cur.second };
		auto curDist{ cur.first };

		if (src == S)
			break;

		if (dist_forward[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };

			auto newDist{ curDist + w };

			if (dist_forward[dst] > newDist)
			{
				dist_forward[dst] = newDist;
				myPQ.push({ newDist,dst });
				parent[dst] = src;
			}
			else if (dist_forward[dst] == newDist)
			{
				parent[dst] = min(parent[dst], src);
			}
		}
	}

	int cursor{ parent[S] };

	while (true)
	{
		if (cursor == E)
			break;

		visited[cursor] = true;
		cursor = parent[cursor];
	}

	result += dist_forward[S];
}

void dijkstra_reverse()
{
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> myPQ;
	myPQ.push({ 0,E });
	dist_reverse[E] = 0;

	while (myPQ.empty() == false)
	{
		auto cur{ myPQ.top() };
		myPQ.pop();

		auto src{ cur.second };
		auto curDist{ cur.first };

		if (src == S)
			break;

		if (dist_reverse[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };

			auto newDist{ curDist + w };

			if (visited[dst] == true)
				continue;

			if (dist_reverse[dst] > newDist)
			{
				dist_reverse[dst] = newDist;
				myPQ.push({ newDist,dst });
			}
		}
	}

	result += dist_reverse[S];
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	cin >> S >> E;

	dijkstra_forward();
	dijkstra_reverse();

	cout << result;

	return 0;
}