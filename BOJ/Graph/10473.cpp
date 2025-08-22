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
using vertex = tuple<double, int>;

#define endl '\n'
#define INF numeric_limits<double>::max()
#define MAX 101

int N{ 0 };
vector<pair<double, double>> vertexes;
vector<double> dist(MAX, INF);
pair<double, double> start;
pair<double, double> goal;

void input()
{
	cin >> start.first >> start.second;
	cin >> goal.first >> goal.second;

	cin >> N;

	vertexes.push_back({ start.first,start.second });

	for (int i{ 0 }; i < N; ++i)
	{
		double x{ 0 }, y{ 0 };
		cin >> x >> y;

		vertexes.push_back({ x,y });
	}

	vertexes.push_back({ goal.first,goal.second });
}

double getDist(pair<double, double> src, pair<double, double> dst)
{
	return hypot(fabs(src.first - dst.first), fabs(src.second - dst.second));
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
		auto curDist{ get <0>(cur) };

		if (dist[src] < curDist)
			continue;

		for (int i{ 1 }; i < N + 2; ++i)
		{
			if (src == i)
				continue;

			auto dst{ vertexes[i] };
			double w{ 0 };

			if (src == 0)
				w = getDist(start, dst);
			else
				w = getDist(vertexes[src], dst);

			auto time{ min(w / 5,fabs(w - 50) / 5 + 2) };

			if (src == 0)
				time = w / 5;

			if (dist[i] > curDist + time)
			{
				dist[i] = curDist + time;
				pq.push({ dist[i],i });
			}
		}
	}
}

void solve()
{
	dijkstra();

	cout << dist[N + 1];
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