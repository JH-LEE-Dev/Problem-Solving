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
*	문제 해결 전략
*	1. 다익스트라 알고리즘으로, 미팅하는 사람들의 정점에서 각 정점까지의 거리를 구한다.
*	2. 다익스트라 알고리즘의 거리는 시작 정점에서 도착 정점까지의 가중치 총 합의 제곱이다.
*	   가중치의 총 합과 제곱은 값이 다르므로, 각 정점의 거리는 총합의 제곱으로 하고, pq 원소에 가중치 총 합을
*	   삽입하여 경로의 총 가중치 합을 보존한다.
*/

using namespace std;
using ll = long long;
using vertex = tuple<ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 101

int T;
int N, P, Q;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> people;
vector<vector<ll>> dist(MAX, vector<ll>(MAX, INF));

void input()
{
	people.clear();
	edges = vector<vector<pair<int, int>>>(MAX, vector<pair<int, int>>());
	dist = vector<vector<ll>>(MAX, vector<ll>(MAX, INF));

	cin >> N >> P >> Q;

	for (int i{ 0 }; i < N; ++i)
	{
		int num;
		cin >> num;

		people.push_back(num);
	}

	for (int i{ 0 }; i < Q; ++i)
	{
		int src, dst, w;
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}
}

void dijkstra(int start)
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,start });
	dist[start][start] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curWeight{ get<0>(cur) };

		if (dist[start][src] < curWeight * curWeight)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newWeight{ curWeight + w };
			auto newDist{ newWeight * newWeight };

			if (dist[start][dst] > newDist)
			{
				dist[start][dst] = newDist;
				pq.push({ newWeight,dst });
			}
		}
	}
}

void solve()
{
	cin >> T;

	for (int i{ 0 }; i < T; ++i)
	{
		input();

		for (int i{ 0 }; i < N; ++i)
		{
			dijkstra(people[i]);
		}

		ll result{ INF };
		int minVertex{ 0 };

		for (int i{ 1 }; i <= P; ++i)
		{
			ll totalDist{ 0 };
			bool isValid{ true };

			for (int j{ 0 }; j < N; ++j)
			{
				int curPerson{ people[j] };

				if (dist[curPerson][i] == INF)
				{
					//미팅 장소에 한 명이라도 도달할 수 없으면 후보에서 제외.
					isValid = false;
					break;
				}

				totalDist += dist[curPerson][i];
			}

			if (isValid == false)
				continue;

			if (result > totalDist)
			{
				result = totalDist;
				minVertex = i;
			}
		}

		cout << minVertex << ' ' << result << endl;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}