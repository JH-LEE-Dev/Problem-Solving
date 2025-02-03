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
#define MAX 52

int N{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<pair<char, char>> result;

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		string str;
		char c1, c2;
		int src{ 0 }, dst{ 0 };
		int len{ 0 };

		cin >> c1 >> str >> c2;

		if (c1 - 'a' >= 0)
		{
			src = c1 - 'a';
		}
		else
		{
			src = c1 - 'A' + 26;
		}

		if (c2 - 'a' >= 0)
		{
			dst = c2 - 'a';
		}
		else
		{
			dst = c2 - 'A' + 26;
		}

		dist[src][dst] = 1;
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

	for (int i{ 0 }; i < MAX; ++i)
	{
		for (int j{ 0 }; j < MAX; ++j)
		{
			if (i == j)
				continue;

			if (dist[i][j] != INF)
			{
				char src, dst;

				if (i < 26)
				{
					src = i + (int)('a');
				}
				else
				{
					src = (i - 26) + (int)('A');
				}

				if (j < 26)
				{
					dst = j + (int)('a');
				}
				else
				{
					dst = (j - 26) + (int)('A');
				}

				result.push_back({ src,dst });
			}
		}
	}

	sort(result.begin(), result.end());

	cout << result.size() << endl;

	for (auto& str : result)
	{
		cout << str.first << " => " << str.second << endl;
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