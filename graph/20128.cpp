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
*	1. ���ͽ�Ʈ�� �˰����� ����Ѵ�. �Ÿ� �迭�� 2�����̰� Ȧ���� ¦�� �Ÿ��� ������ �����ϱ� �����̴�.
*	2. �Ÿ� �迭�� Ȧ���� ¦���� ������ ������, ���� ��� v�� ������ Ȧ���� ������ �Ÿ����� ¦���� ������ �Ÿ��� �� ������, Ȧ��
*		��δ� pruning�Ǿ� ¦�� ��θ� ��Ƴ��´�. v+1�� ������ ¦�� ��ΰ� Ȧ�� ��η� �ٲ�� �����Ѵٸ�, ¦�� ��θ� ����� �� ����.
*		�� v�� ������ �Ÿ��� �� ����� Ȧ���� �� �� �ִ� ��ΰ� �־�� v+1�� ������ ¦�� ��θ� ����� �� �ִ�.
*/

using namespace std;
using ll = long long;
using vertex = tuple<ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 100'001

int N, M;

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<ll>> dist(MAX, vector<ll>(2, INF));

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
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,1 });

	dist[1][0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src][curDist % 2] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst][newDist % 2] > newDist)
			{
				dist[dst][newDist % 2] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	dijkstra();

	for (int i{ 1 }; i <= N; ++i)
	{
		if (dist[i][1] == INF)
			cout << -1 << ' ';
		else
			cout << dist[i][1] << ' ';

		if (dist[i][0] == INF)
			cout << -1 << endl;
		else
			cout << dist[i][0] << endl;
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