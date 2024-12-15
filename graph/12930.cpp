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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 22

int N{ 0 };
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>(MAX, { -1,-1 }));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

int result{ -1 };

void dijkstra()
{
	priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<tuple<int, int, int, int>>> myPQ;
	myPQ.push({ 0,0,0,0 });

	while (myPQ.empty() == false)
	{
		auto cur{ myPQ.top() };
		myPQ.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto totalW1{ get<2>(cur) };
		auto totalW2{ get<3>(cur) };

		if (src == 1)
		{
			result = curDist;
			return;
		}

		if (totalW1 > dist[0][src] && totalW2 > dist[1][src])
			continue;

		for (int dst{ 0 }; dst < N; ++dst)
		{
			if (edges[src][dst].first == -1 && edges[src][dst].second == -1)
				continue;

			auto w1{ edges[src][dst].first };
			auto w2{ edges[src][dst].second };

			auto totalDist{ (totalW1 + w1) * (totalW2 + w2) };

			if (dist[0][dst] > totalW1 + w1 || dist[1][dst] > totalW2 + w2)
			{
				dist[0][dst] = min(dist[0][dst], totalW1 + w1);
				dist[1][dst] = min(dist[1][dst], totalW2 + w2);

				myPQ.push({ totalDist,dst,totalW1 + w1 ,totalW2 + w2 });
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		string w;
		cin >> w;

		for (int j{ 0 }; j < N; ++j)
		{
			int input;

			if (w[j] == '.')
			{
				input = -1;
			}
			else
			{
				input = w[j] - '0';
			}

			edges[i][j].first = input;
			edges[j][i].first = input;
		}
	}

	for (int i{ 0 }; i < N; ++i)
	{
		string w;
		cin >> w;

		for (int j{ 0 }; j < N; ++j)
		{
			int input;

			if (w[j] == '.')
			{
				input = -1;
			}
			else
			{
				input = w[j] - '0';
			}

			edges[i][j].second = input;
			edges[j][i].second = input;
		}
	}

	dijkstra();

	cout << result;

	return 0;
}