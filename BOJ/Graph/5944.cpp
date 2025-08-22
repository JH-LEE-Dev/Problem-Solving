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
*	���� �м�
*	1. �� ���� ������ �־�����. �ϳ��� ��� �����̰�, ������ �� ������ �����ؾ� �ϴ� �����̴�.
*	2. ����� �׷����̰�, �׷����� ���� �׷����̴�.
*
*	���� �ذ� ����
*	1. ��� �������� ���ͽ�Ʈ�� �˰����� �����Ͽ� ������ �� ���������� �Ÿ��� ���Ѵ�.
*	2. �� ������ ���� �߿��� � ������ ���� �湮���� �� �ִ� ��ΰ� �������� Ȯ���ϱ� ���ؼ� �� ������ ����������
*	   �ϴ� ���ͽ�Ʈ�� �˰����� �����Ѵ�.
*	3. �� �������� A,B��� �� ��, dist[A] + dist_A[B] �� dist[B] + dist_B[A] �߿��� �ּҰ��� �������� �����Ѵ�.
*/
using namespace std;
using vertex = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 100'001

int C, P, PB, PA1, PA2;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist(MAX, INF);
vector<int> dist_A(MAX, INF);
vector<int> dist_B(MAX, INF);

void input()
{
	cin >> C >> P >> PB >> PA1 >> PA2;

	for (int i{ 0 }; i < C; ++i)
	{
		int  src, dst, w;

		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra(int start, int type)
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	switch (type)
	{
	case 0:
		pq.push({ 0,PB });
		dist[PB] = 0;
		break;
	case 1:
		pq.push({ 0,PA1 });
		dist_A[PA1] = 0;
		break;
	case 2:
		pq.push({ 0,PA2 });
		dist_B[PA2] = 0;
		break;
	}

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		switch (type)
		{
		case 0:
			if (dist[src] < curDist)
				continue;
			break;
		case 1:
			if (dist_A[src] < curDist)
				continue;
			break;
		case 2:
			if (dist_B[src] < curDist)
				continue;
			break;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			switch (type)
			{
			case 0:
				if (dist[dst] > newDist)
				{
					dist[dst] = newDist;
					pq.push({ newDist,dst });
				}
				break;
			case 1:

				if (dist_A[dst] > newDist)
				{
					dist_A[dst] = newDist;
					pq.push({ newDist,dst });
				}
				break;
			case 2:

				if (dist_B[dst] > newDist)
				{
					dist_B[dst] = newDist;
					pq.push({ newDist,dst });
				}
				break;
			}
		}
	}
}

void solve()
{
	dijkstra(PB, 0);
	dijkstra(PA1, 1);
	dijkstra(PA2, 2);

	int result{ INF };

	result = min(dist[PA1] + dist_A[PA2], dist[PA2] + dist_B[PA1]);

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