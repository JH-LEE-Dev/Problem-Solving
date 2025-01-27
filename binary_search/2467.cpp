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
ll liquid_1{ 0 };
ll liquid_2{ 0 };

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;

		liquids.push_back(input);
	}

	sort(liquids.begin(), liquids.end());
}

void bSearch()
{
	for (int i{ 0 }; i < N - 1; ++i)
	{
		int left{ i + 1 };
		int right{ N - 1 };
		int middle{ 0 };

		while (left <= right)
		{
			middle = (left + right) / 2;

			ll sum{ liquids[i] + liquids[middle] };

			if (abs(sum) < result)
			{
				liquid_1 = liquids[i];
				liquid_2 = liquids[middle];
				result = abs(sum);
			}

			if (sum == 0)
				return;

			if (sum < 0)
			{
				left = middle + 1;
			}

			if (sum > 0)
			{
				right = middle - 1;
			}
		}
	}
}

void solve()
{
	bSearch();

	cout << liquid_1 << ' ' << liquid_2;
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