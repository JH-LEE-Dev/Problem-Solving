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
using ll = long long;

#define endl '\n'
#define INF numeric_limits<ll>::max()

int N{ 0 };
vector<ll> liquids;
ll result{ INF };
vector<int> result_liquids(3, -1);

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;

		liquids.push_back(input);
	}
}

int bSearch(int l, int r, ll sum)
{
	int left{ l };
	int right{ r };
	int middle{ 0 };
	int curSum{ 0 };

	ll minSum{ INF };

	int idx{ 0 };

	while (left <= right)
	{
		middle = (left + right) / 2;
		curSum = abs(liquids[middle] + sum);

		if (liquids[middle] + sum < 0)
		{
			if (minSum > curSum)
			{
				minSum = curSum;
				idx = middle;
			}

			left = middle + 1;
		}

		if (liquids[middle] + sum > 0)
		{
			if (minSum > curSum)
			{
				minSum = curSum;
				idx = middle;
			}

			right = middle - 1;
		}

		if (liquids[middle] + sum == 0)
		{
			return middle;
		}
	}

	return idx;
}

void solve()
{
	sort(liquids.begin(), liquids.end());

	for (int i{ 0 }; i < N - 2; ++i)
	{
		for (int j{ i + 1 }; j < N - 1; ++j)
		{
			int idx{ bSearch(j + 1,N - 1,liquids[i] + liquids[j]) };

			ll sum{ abs(liquids[i] + liquids[j] + liquids[idx]) };

			if (sum < result)
			{
				result = sum;
				result_liquids[0] = liquids[i];
				result_liquids[1] = liquids[j];
				result_liquids[2] = liquids[idx];
			}
		}
	}

	cout << result_liquids[0] << ' ' << result_liquids[1] << ' ' << result_liquids[2];
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