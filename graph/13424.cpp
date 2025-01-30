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

#define endl '\n'
#define INF numeric_limits<int>::max()/2
#define MAX 101

int N{ 0 }, M{ 0 }, T{ 0 }, K{ 0 };
vector<vector<int>> dist;
vector<int> friends;
vector<int> totalDist;

void input()
{
	cin >> T;
}

void input_graph()
{
	cin >> N >> M;

	dist = vector<vector<int>>(MAX, vector<int>(MAX, INF));
	totalDist = vector<int>(MAX, 0);

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		dist[src][dst] = w;
		dist[dst][src] = w;
	}

	cin >> K;

	friends.clear();

	for (int i{ 0 }; i < K; ++i)
	{
		int input{ 0 };
		cin >> input;

		friends.push_back(input);
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
				dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
			}
		}
	}
}

void solve()
{
	while (T != 0)
	{
		input_graph();

		floydWarshall();

		for (int i{ 1 }; i <= N; ++i)
		{
			for (int j{ 0 }; j < K; ++j)
			{
				totalDist[i] += dist[friends[j]][i];
			}
		}

		int room{ 0 };
		int compareDist{ INF };

		for (int i{ 1 }; i <= N; ++i)
		{
			if (totalDist[i] < compareDist)
			{
				compareDist = totalDist[i];
				room = i;
			}
		}

		cout << room << endl;

		--T;
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