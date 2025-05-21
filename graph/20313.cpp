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
using vertex = tuple<ll, int, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 1'001

int N, M, K, A, B;
vector<vector<tuple<int, int, int>>> edges(MAX, vector<tuple<int, int, int>>());
vector<vector<ll>> magicEdge(101, vector<ll>());
vector<vector<ll>> dist(101, vector<ll>(MAX, INF));

ll result{ 0 };

void input()
{
	cin >> N >> M >> A >> B;

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst, w;
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w,i });
		edges[dst].push_back({ src,w,i });

		magicEdge[0].push_back(w);
	}

	cin >> K;

	for (int i{ 1 }; i <= K; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			int temp;
			cin >> temp;

			magicEdge[i].push_back(temp);
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0,A });
	dist[0][A] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<2>(cur) };
		auto curDist{ get<0>(cur) };
		auto curK{ get<1>(cur) };

		if (dist[curK][src] < curDist)
			continue;

		if (src == B)
		{
			result = curDist;
			return;
		}

		for (auto& edge : edges[src])
		{
			auto dst{ get<0>(edge) };
			auto idx{ get<2>(edge) };

			auto w{ magicEdge[curK][idx] };
			auto newDist{ curDist + w };

			if (dist[curK][dst] > newDist)
			{
				dist[curK][dst] = newDist;
				pq.push({ newDist,curK,dst });
			}

			for (int i{ curK + 1 }; i <= K; ++i)
			{
				w = magicEdge[i][idx];
				newDist = curDist + w;

				if (dist[i][dst] > newDist)
				{
					dist[i][dst] = newDist;
					pq.push({ newDist,i,dst });
				}
			}
		}
	}
}

void solve()
{
	dijkstra();

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