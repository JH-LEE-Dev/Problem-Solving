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

#define MAX 101
#define endl '\n'
#define INF numeric_limits<int>::max()/2

int N{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> dist[i][j];
			if (dist[i][j] == 0)
				dist[i][j] = INF;
		}
	}
}

void floydWarshall()
{
	for (int middle{ 0 }; middle < N; ++middle)
	{
		for (int left{ 0 }; left < N; ++left)
		{
			for (int right{ 0 }; right < N; ++right)
			{
				dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
			}
		}
	}
}

void solve()
{
	floydWarshall();

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			if (dist[i][j] != INF)
				cout << 1 << ' ';
			else
				cout << 0 << ' ';
		}

		cout << endl;
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