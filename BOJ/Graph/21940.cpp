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

#define MAX 201
#define endl '\n'
#define INF numeric_limits<int>::max()/2

int N{ 0 }, M{ 0 }, K{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<int> friends;
vector<int> result;

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, w{ 0 };
		cin >> src >> dst >> w;

		dist[src][dst] = w;
	}

	cin >> K;

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
	floydWarshall();

	int totalDist{ INF };

	for (int i{ 1 }; i <= N; ++i)
	{
		auto RT_Dist{ -1 };

		for (int j{ 0 }; j < K; ++j)
		{
			if (dist[friends[j]][i] == INF || dist[i][friends[j]] == INF)
			{
				RT_Dist = INF;
				break;
			}

			if (RT_Dist < dist[friends[j]][i] + dist[i][friends[j]])
			{
				RT_Dist = dist[friends[j]][i] + dist[i][friends[j]];
			}
		}

		if (RT_Dist < totalDist)
		{
			totalDist = RT_Dist;
			result.clear();
			result.push_back(i);
		}
		else if (RT_Dist == totalDist)
		{
			result.push_back(i);
		}
	}

	for (auto& it : result)
	{
		cout << it << ' ';
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