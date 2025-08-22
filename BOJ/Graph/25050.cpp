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

#define MAX 2'001
#define MAX_EDGE 5'001
#define endl '\n'
#define INF numeric_limits<ll>::max()

vector<vector< tuple<int, int>>> edges(MAX, vector< tuple<int, int>>());
vector<int> scores(MAX_EDGE, 0);
vector<vector<int>> tree(MAX, vector<int>());
vector<vector<int>> idx(MAX, vector<int>(MAX, 0));

int N{ 0 }, M{ 0 };

using vertex = tuple<ll, int, int>;

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		edges[src].push_back({ dst,w });
		idx[src][dst] = i;
	}
}

void dijkstra(int start)
{
	vector<ll> dist(MAX, INF);

	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,start,-1 });
	dist[start] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto parent{ get<2>(cur) };

		if (dist[src] < curDist)
			continue;

		if (parent != -1)
			tree[parent].push_back(src);

		for (auto& edge : edges[src])
		{
			auto dst{ get<0>(edge) };
			auto w{ get<1>(edge) };
			auto newDist{ curDist + w };

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst,src });
			}
		}
	}
}

int dfs(int root)
{
	int cnt{ 1 };

	for (auto& subTree : tree[root])
	{
		int subTreeCnt = dfs(subTree);
		scores[idx[root][subTree]] += subTreeCnt;
		cnt += subTreeCnt;
	}

	return cnt;
}

void solve()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		tree = vector<vector<int>>(MAX, vector<int>());
		dijkstra(i);
		dfs(i);
	}

	auto maxScore{ -1 };
	vector<int> result;

	for (int i{ 0 }; i < M; ++i)
	{
		if (maxScore < scores[i])
		{
			result.clear();
			result.push_back(i + 1);
			maxScore = scores[i];
		}
		else if (maxScore == scores[i])
		{
			result.push_back(i + 1);
		}
	}

	auto cnt{ result.size() };
	cout << cnt << endl;
	for (int i{ 0 }; i < cnt; ++i)
	{
		cout << result[i] << ' ';
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}