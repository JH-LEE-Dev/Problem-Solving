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
using vertex = tuple<int, int>;
#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int N, M, A, B, C;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<int>> edgesForResult(MAX, vector<int>(MAX, INF));
vector<int> dist_A(MAX, INF);
vector<int> dist_B(MAX, INF);
vector<int> dist_C(MAX, INF);
vector<bool> visited(MAX, false);
vector<int> parent_A(MAX, -1);
vector<int> parent_B(MAX, -1);
vector<int> parent_C(MAX, -1);

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
		edgesForResult[src][dst] = w;
		edgesForResult[dst][src] = w;
	}

	cin >> A >> B >> C;
}

void dijkstra(int start, vector<int>& _dist, vector<int>& _parent)
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,start });
	_dist[start] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (_dist[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (_dist[dst] > newDist)
			{
				_dist[dst] = newDist;
				pq.push({ newDist,dst });
				_parent[dst] = src;
			}
		}
	}
}

void solve()
{
	dijkstra(A, dist_A, parent_A);
	dijkstra(B, dist_B, parent_B);
	dijkstra(C, dist_C, parent_C);

	int minVertex{ 0 };
	int minDist{ INF };

	for (int i{ 1 }; i <= N; ++i)
	{
		int temp{ dist_A[i] + dist_B[i] + dist_C[i] };

		if (minDist > temp)
		{
			minDist = temp;
			minVertex = i;
		}
	}

	int total{ 0 };
	int cnt{ 0 };

	vector<pair<int, int>> resultEdges;

	int cursor{ minVertex };

	while (cursor != -1)
	{
		if (parent_A[cursor] == -1)
			break;

		visited[cursor] = true;
		resultEdges.push_back({ parent_A[cursor],cursor });

		total += edgesForResult[parent_A[cursor]][cursor];
		cursor = parent_A[cursor];

		++cnt;
	}

	cursor = minVertex;

	while (cursor != -1)
	{
		if (parent_B[cursor] == -1)
			break;

		visited[cursor] = true;
		resultEdges.push_back({ parent_B[cursor],cursor });

		total += edgesForResult[parent_B[cursor]][cursor];
		cursor = parent_B[cursor];

		++cnt;
	}

	cursor = minVertex;

	while (cursor != -1)
	{
		if (parent_C[cursor] == -1)
			break;

		visited[cursor] = true;
		resultEdges.push_back({ parent_C[cursor],cursor });

		total += edgesForResult[parent_C[cursor]][cursor];
		cursor = parent_C[cursor];

		++cnt;
	}

	cout << total << ' ' << cnt << endl;

	for (auto& edge : resultEdges)
	{
		cout << edge.first << ' ' << edge.second << endl;
	}
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