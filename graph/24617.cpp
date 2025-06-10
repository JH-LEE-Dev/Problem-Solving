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
#define MAX 501

int N;
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<vector<int>> prefer(MAX, vector<int>(MAX, INF));

void input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		bool bValid{ true };

		for (int j{ 1 }; j <= N; ++j)
		{
			int temp;
			cin >> temp;

			if (temp == i)
				bValid = false;

			if (bValid)
			{
				dist[i][temp] = 1;
				prefer[i][temp] = j;
			}
		}
	}
}

void floydWarshall()
{
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

	for (int i{ 1 }; i <= N; ++i)
	{
		int priority{ prefer[i][i] };
		int min{ i };

		for (int j{ 1 }; j <= N; ++j)
		{
			if (dist[i][j] == 1 && dist[j][i] != INF && priority >= prefer[i][j])
			{
				min = j;
				priority = prefer[i][j];
			}
		}

		cout << min << endl;
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