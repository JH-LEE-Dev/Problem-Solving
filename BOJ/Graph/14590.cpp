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

/*
*	문제 해결 전략
*	1. dfs로 1번부터 시작해서 가장 깊게 들어갈 수 있는 경우를 찾는다.
*	2. dist[v]를 갱신하는 과정에서 child 배열의 값도 갱신하여 1번부터 경로를 복원할 수 있도록 한다.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 21

int N;
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
long long maxBit;
vector<int> dist(MAX, INF);
vector<int> child(MAX, -1);

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> table[i][j];
		}
	}

	maxBit = (1 << N) - 1;
}

int dfs(int v, int curBit)
{
	if (curBit == maxBit)
		return 0;

	if (dist[v] != INF)
		return dist[v];

	dist[v] = 0;

	for (int i{ 0 }; i < N; ++i)
	{
		if (table[v][i] == 0)
			continue;

		if ((curBit & (1 << i)) == (1 << i))
			continue;

		auto nxtResult{ dfs(i, (curBit | (1 << i))) + 1 };

		if (dist[v] < nxtResult)
		{
			dist[v] = nxtResult;
			child[v] = i;
		}
	}

	return dist[v];
}

void solve()
{
	cout << dfs(0, 1) + 1 << endl;

	auto cursor{ 0 };

	while (cursor != -1)
	{
		cout << cursor + 1 << ' ';

		if (child[cursor] == -1)
			break;

		cursor = child[cursor];
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