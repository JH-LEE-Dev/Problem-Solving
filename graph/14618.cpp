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
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 5'001

int N, M, J, K;
set<int> A;
set<int> B;
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist(MAX, INF);
vector<int> distA;
vector<int> distB;

void input()
{
	cin >> N >> M >> J >> K;

	for (int i{ 0 }; i < K; ++i)
	{
		int temp;
		cin >> temp;

		A.insert(temp);
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int temp;
		cin >> temp;

		B.insert(temp);
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
	pq.push({ 0,J,-1 });
	dist[J] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curType{ get<2>(cur) };

		if (dist[src] < curDist)
			continue;

		if (curType == 0)
		{
			distA.push_back(curDist);
		}
		if (curType == 1)
		{
			distB.push_back(curDist);
		}

		for (auto& edge : edges[src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };
			auto newType{ -1 };

			if (A.find(dst) != A.end())
			{
				newType = 0;
			}

			if (B.find(dst) != B.end())
			{
				newType = 1;
			}

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst,newType });
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (distA.size() == 0 && distB.size() == 0)
	{
		cout << -1;
		return;
	}

	if (distA.size() == 0)
	{
		cout << 'B' << endl;
		cout << distB[0];

		return;
	}
	else if (distB.size() == 0)
	{
		cout << 'A' << endl;
		cout << distA[0];

		return;
	}

	auto resultA{ distA[0] };
	auto resultB{ distB[0] };

	if (resultA > resultB)
	{
		cout << 'B' << endl;
		cout << resultB;
	}
	else
	{
		cout << 'A' << endl;
		cout << resultA;
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