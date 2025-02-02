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

ll N{ 0 };
vector<ll> liquids;
vector<ll> result(3, -1);
ll two{ 0 }, three{ 0 };

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int liquid;
		cin >> liquid;

		liquids.push_back(liquid);
	}
}

ll twoP(int l, int r, ll num)
{
	int left{ l };
	int right{ r };
	ll temp{ INF };

	while (left < right)
	{
		ll total = liquids[left] + liquids[right] + num;

		if (total > 0)
		{
			if (temp > abs(total))
			{
				temp = abs(total);
				two = liquids[left];
				three = liquids[right];
			}

			--right;
		}

		if (total < 0)
		{
			if (temp > abs(total))
			{
				temp = abs(total);
				two = liquids[left];
				three = liquids[right];
			}

			++left;
		}

		if (total == 0)
		{
			two = liquids[left];
			three = liquids[right];

			return total;
		}
	}

	return temp;
}

void solve()
{
	sort(liquids.begin(), liquids.end());

	ll temp{ INF };

	for (int i{ 0 }; i < N - 2; ++i)
	{
		ll total{ abs(twoP(i + 1, N - 1, liquids[i])) };

		if (total < temp)
		{
			temp = total;
			result[0] = liquids[i];
			result[1] = two;
			result[2] = three;
		}
	}

	cout << result[0] << ' ' << result[1] << ' ' << result[2];
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