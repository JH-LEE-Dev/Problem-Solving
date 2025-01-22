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
#define INF numeric_limits<int>::max()/2

int N{ 0 }, M{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<int> unionNums(MAX, -1);
vector<int> maxDists(MAX, INF);
vector<int> presidents(MAX, -1);

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 };
		cin >> src >> dst;

		dist[src][dst] = 1;
		dist[dst][src] = 1;
	}
}

void floydWarshall()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		dist[i][i] = 0;
	}

	for (int middle{ 1 }; middle <= N; ++middle)
	{
		for (int left{ 1 }; left <= N; ++left)
		{
			for (int right{ 1 }; right <= N; ++right)
			{
				if (dist[left][right] > dist[left][middle] + dist[middle][right])
				{
					dist[left][right] = dist[left][middle] + dist[middle][right];
				}
			}
		}
	}
}

void solve()
{
	floydWarshall();

	int unions{ -1 };

	for (int i{ 1 }; i <= N; ++i)
	{
		auto curUnions{ unions };
		auto maxDist{ 0 };

		if (unionNums[i] == -1)
		{
			++unions;
			unionNums[i] = unions;
			curUnions = unions;

			presidents[curUnions] = i;
		}
		else
			curUnions = unionNums[i];

		for (int j{ 1 }; j <= N; ++j)
		{
			if (i == j)
				continue;

			if (dist[i][j] != INF)
			{
				unionNums[j] = curUnions;

				maxDist = max(maxDist, dist[i][j]);
			}
		}

		if (maxDists[curUnions] > maxDist)
		{
			presidents[curUnions] = i;
			maxDists[curUnions] = maxDist;
		}
	}

	sort(presidents.begin(), presidents.begin() + unions + 1);

	cout << unions + 1 << endl;

	for (int i{ 0 }; i <= unions; ++i)
	{
		cout << presidents[i] << endl;
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