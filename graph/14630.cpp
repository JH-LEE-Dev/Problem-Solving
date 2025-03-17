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
#define MAX 1'001
#define endl '\n'
#define INF numeric_limits<int>::max()

int N;
vector<string> arr;
vector<int> dist(MAX, INF);
vector<vector<int>> edges(MAX, vector<int>(MAX, INF));
int s, e;

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		string temp;
		cin >> temp;

		arr.push_back(temp);
	}

	cin >> s >> e;
}

void generateGraph()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			if (i == j)
			{
				edges[i][j] = 0;
				continue;
			}

			string A{ arr[i] };
			string B{ arr[j] };
			int w{ 0 };

			for (int k{ 0 }; k < A.length(); ++k)
			{
				int aNum{ A[k] - '0' };
				int bNum{ B[k] - '0' };

				int delta{ aNum - bNum };
				delta *= delta;

				w += delta;
			}

			edges[i][j] = w;
			edges[j][i] = w;
		}
	}
}


void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,s - 1 });
	dist[s - 1] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		for (int i{ 0 }; i < N; ++i)
		{
			if (i == src)
				continue;

			int w{ edges[src][i] };
			int newDist{ curDist + w };

			if (dist[i] > newDist)
			{
				pq.push({ newDist,i });
				dist[i] = newDist;
			}
		}
	}
}

void solve()
{
	generateGraph();
	dijkstra();

	cout << dist[e - 1];
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