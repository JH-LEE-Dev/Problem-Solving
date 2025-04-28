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

/*
*	���� �ذ� ����
*	1. �ּ� 3���� �߰� ������ �湮�ؾ� �Ѵٸ�, 3�� �̻� �湮�� ���� �ִ� �Ÿ��� �� �� ����. �ݵ�� �ּ� �湮 ������ 3�� �湮�� ��찡
*	�ִ� �Ÿ��� ���̴�.
*	2. ���� ���ͽ�Ʈ�� �˰����� ������, �߰� �����鿡 ���ؼ� �����ϰ� dfs�� �����Ͽ� ��Ʈ��ŷ���� ��� ����� ���� Ž���ߴ�.
*/

using namespace std;
using ll = long long;
using vertex = tuple<ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 100'001

int N, M, start, goal, P;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> stopBy;

vector<vector<ll>> dist(MAX, vector<ll>(101, INF));

vector<bool> visited(MAX, false);

ll result{ INF };

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	cin >> start >> goal;
	cin >> P;

	for (int i{ 0 }; i < P; ++i)
	{
		int temp;
		cin >> temp;

		stopBy.push_back(temp);
	}
}

void dijkstra(int v, int idx)
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	dist[v][idx] = 0;
	pq.push({ 0,v });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src][idx] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst][idx] > newDist)
			{
				dist[dst][idx] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void dfs(int v, ll curDist, int cnt, int idx)
{
	if (cnt >= 3)
	{
		if (dist[goal][idx] != INF)
			result = min(result, curDist + dist[goal][idx]);

		return;
	}

	visited[v] = true;

	for (int i{ 0 }; i < P; ++i)
	{
		if (visited[stopBy[i]] == false && dist[stopBy[i]][idx] != INF)
			dfs(stopBy[i], curDist + dist[stopBy[i]][idx], cnt + 1, i);
	}

	visited[v] = false;
}

void solve()
{
	dijkstra(start, 100);

	for (int i{ 0 }; i < P; ++i)
	{
		dijkstra(stopBy[i], i);
	}

	dfs(start, 0, 0, 100);

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