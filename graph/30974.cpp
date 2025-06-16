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
using ll = long long;
using vertex = tuple<ll, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 400'001
#define MAX_NUM 10'000'001

int N, M;
vector<bool> prime(MAX_NUM, true);
vector<int> weights(MAX, 0);

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<ll> dist(MAX, INF);

ll result{ INF };
int maxPrime{ 0 };

void primeNumber()
{
	prime[0] = false;
	prime[1] = false;

	for (int i{ 2 }; i * i <= maxPrime; ++i)
	{
		if (prime[i])
		{
			for (int j{ i * i }; j <= maxPrime; j += i)
			{
				prime[j] = false;
			}
		}
	}
}

void input()
{
	cin >> N >> M;

	for (int i{ 1 }; i <= N; ++i)
	{
		cin >> weights[i];
		maxPrime = max(maxPrime, weights[i] * 2);
	}

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
	dist[1] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		if (src == N)
		{
			result = curDist;
			return;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (prime[weights[src] + weights[dst]] == false)
				continue;

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	primeNumber();

	dijkstra();

	if (result == INF)
		cout << "Now where are you?";
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