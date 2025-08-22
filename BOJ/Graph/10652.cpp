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
*	1. Bessie�� Elsie�� ���������� �ϴ� ���ͽ�Ʈ���, ���� �������� P�� ����ġ�� ����ϴ� ���ͽ�Ʈ�� ����.
*	2. ������ ���� ���� ���� ���� ��츦 ���Ͽ� �� ���� ��츦 ������ ����
*/

using namespace std;
using ll = long long;
using vertex = tuple<ll, int, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 40'001

int Bessie{ 1 }, Elsie{ 2 }, Together{ 3 };
vector<vector<int>> edges(MAX, vector<int>());
int B, E, P, N, M;

//Bessie,Elsie,Together�� ���� �ε����� ���� ���ؼ� dist�� 1������ 4�� ����(out of range ����)
vector<vector<ll>> dist(4, vector<ll>(MAX, INF));

void input()
{
	cin >> B >> E >> P >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst;

		cin >> src >> dst;

		edges[src].push_back({ dst });
		edges[dst].push_back({ src });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,Bessie,Bessie });
	pq.push({ 0,Elsie,Elsie });
	pq.push({ 0,N,Together });
	dist[Bessie][Bessie] = 0;
	dist[Elsie][Elsie] = 0;
	dist[Together][N] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curType{ get<2>(cur) };

		if (dist[curType][src] < curDist)
			continue;

		for (auto& dst : edges[src])
		{
			auto w{ 0 };

			if (curType == Bessie)
			{
				w = B;
			}

			if (curType == Elsie)
			{
				w = E;
			}

			if (curType == Together)
			{
				w = P;
			}

			auto newDist{ curDist + w };

			if (dist[curType][dst] > newDist)
			{
				dist[curType][dst] = newDist;
				pq.push({ newDist,dst,curType });
			}
		}
	}
}

void solve()
{
	dijkstra();

	ll result{ dist[Bessie][N] + dist[Elsie][N] };

	for (int i{ 1 }; i <= N; ++i)
	{
		ll together{ dist[Together][i] + dist[Bessie][i] + dist[Elsie][i] };

		result = min(result, together);
	}

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