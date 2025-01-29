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
#define MAX 27

int N{ 0 }, Q{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<pair<int, int>> query;

void input()
{
	cin >> N;
	cin.ignore();

	for (int i{ 0 }; i < N; ++i)
	{
		string temp;
		getline(cin, temp);

		int len{ (int)temp.length() };
		int src{ temp[0] - 'a' };
		int dst{ temp[len - 1] - 'a' };

		dist[src][dst] = 1;
	}

	cin >> Q;
	cin.ignore();

	for (int i{ 0 }; i < Q; ++i)
	{
		string temp;
		getline(cin, temp);

		int len{ (int)temp.length() };
		int src{ temp[0] - 'a' };
		int dst{ temp[len - 1] - 'a' };

		query.push_back({ src,dst });
	}
}

void floydWarshall()
{
	for (int i{ 0 }; i < MAX; ++i)
	{
		dist[i][i] = 0;
	}

	for (int middle{ 0 }; middle < MAX; ++middle)
	{
		for (int left{ 0 }; left < MAX; ++left)
		{
			for (int right{ 0 }; right < MAX; ++right)
			{
				dist[left][right] = min(dist[left][right], dist[left][middle] + dist[middle][right]);
			}
		}
	}
}

void solve()
{
	floydWarshall();

	for (int i{ 0 }; i < Q; ++i)
	{
		int src{ query[i].first };
		int dst{ query[i].second };

		if (dist[src][dst] != INF)
			cout << 'T' << endl;
		else
			cout << 'F' << endl;
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