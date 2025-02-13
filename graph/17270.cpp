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

#define MAX 101
#define endl '\n'
#define INF numeric_limits<int>::max()

int N{ 0 }, M{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
int A{ 0 }, B{ 0 };
vector<int> dist_A(MAX, INF);
vector<int> dist_B(MAX, INF);

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		edges[dst].push_back({ src,w });
	}

	cin >> A >> B;
}

void dijkstra_A()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,A });
	dist_A[A] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist_A[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist_A[dst] > newDist)
			{
				dist_A[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void dijkstra_B()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,B });
	dist_B[B] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist_B[src] < curDist)
			continue;

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist_B[dst] > newDist)
			{
				dist_B[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	dijkstra_A();
	dijkstra_B();

	int result{ -1 };
	int minDist{ INF };
	int minA{ INF };

	for (int i{ 1 }; i <= N; ++i)
	{
		if (i == A || i == B)
			continue;

		minDist = min(minDist, dist_A[i] + dist_B[i]);
	}

	for (int i = 1; i <= N; ++i)
	{
		if (i == A || i == B)
			continue;

		if (minDist != dist_A[i] + dist_B[i])
			continue;

		if (dist_A[i] > dist_B[i])
			continue;

		if (minA > dist_A[i])
		{
			minA = dist_A[i];
			result = i;
		}
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