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
#define MAX 100'001
int N{ 0 }, K{ 0 };
vector<int> coin;
vector<int> DP_count(MAX, INF);

void input()
{
	cin >> N >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;

		coin.push_back(input);
		DP_count[input] = 1;
	}
}

void solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ coin[i] }; j <= K; ++j)
		{
			if (j >= coin[i])
			{
				DP_count[j] = min(DP_count[j], DP_count[j - coin[i]] + 1);
			}
		}
	}

	if (DP_count[K] == INF)
		cout << -1;
	else
		cout << DP_count[K];
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}