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
* 1.�� ¡�˴ٸ��� ���������� �׷������� ���ͽ�Ʈ�� �˰������� �Ÿ��� ����.
*	- �������� 0,0
*	- �� ���� ������ ��ǥ ���̰� 2 ������ ������θ� �̵��� �� ����.
*	- �Ÿ��� �� ��ǥ ������ ������ ��
* 2.���ͽ�Ʈ�� �˰��� �������� y��ǥ�� ��¼��� �����Ѵٸ�, min�Լ��� �ּڰ��� ���ϸ� ����.
*
* 3.���� ������ �ſ� ũ�� ������, �׷����� �����ϱ⿡�� �ݺ� ���� �ſ� ������ �ð� �ʰ��� �ɸ��Ƿ�
*	���ͽ�Ʈ�� �������� x,y��ǥ ���̰� 2 ������ �������� ã�ƾ� ��.
*		- �̸� ���ؼ� ���� �迭�� y��ǥ�� 1�������� ����, 2������ x��ǥ, 3������ ���� �ε����� ����.
*		- ���ͽ�Ʈ�� �������� �̺� Ž���� Ȱ���Ͽ� y��ǥ -2 ~ +2 �������� x��ǥ ���̰� 2�� �������� ������ Ž��.
*/
using namespace std;
using vertex = tuple<double, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'000'000

int N, F;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<pair<int, int>> vertexes;
vector<double> dist(50'001, (double)INF);

double result{ (double)numeric_limits<int>::max() };

void input()
{
	cin >> N >> F;

	edges[0].push_back({ 0,0 });
	vertexes.push_back({ 0,0 });

	for (int i{ 1 }; i <= N; ++i)
	{
		int x, y;
		cin >> x >> y;

		edges[y].push_back({ x,i });
		vertexes.push_back({ x,y });
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0 });
	dist[0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		auto curX{ vertexes[src].first };
		auto curY{ vertexes[src].second };

		if (curY >= F)
		{
			result = curDist;
			return;
		}

		for (int i{ -2 }; i < 3; ++i)
		{
			if (curY + i < 0 || curY + i > MAX)
				continue;

			auto left{ lower_bound(edges[curY + i].begin(), edges[curY + i].end(), make_pair(curX - 2,-1)) };
			auto right{ upper_bound(edges[curY + i].begin(),edges[curY + i].end(),make_pair(curX + 2,INF)) };

			auto leftIdx{ left - edges[curY + i].begin() };
			auto rightIdx{ right - edges[curY + i].begin() };

			for (int j{ (int)leftIdx }; j < rightIdx; ++j)
			{
				auto dst{ edges[curY + i][j].second };
				auto coord_dst{ vertexes[dst] };
				auto dst_x{ coord_dst.first };
				auto dst_y{ coord_dst.second };

				auto deltaX{ abs(curX - dst_x) };
				auto deltaY{ abs(curY - dst_y) };

				auto distance{ hypot(deltaX,deltaY) };

				auto newDist{ curDist + distance };

				if (dist[dst] > newDist)
				{
					dist[dst] = newDist;
					pq.push({ newDist,dst });
				}
			}
		}
	}
}

void solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		sort(edges[i].begin(), edges[i].end());
	}

	dijkstra();

	if (result == INF)
		cout << -1;
	else
		cout << (int)round(result);
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