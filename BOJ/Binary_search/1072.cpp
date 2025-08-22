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

#define MAX 1'000'000'001
#define endl '\n'
#define INF numeric_limits<ll>::max()

ll X{ 0 }, Y{ 0 }, result{ INF };

void input()
{
	cin >> X >> Y;
}

void bSearch()
{
	ll init = Y * 100 / X;

	ll left{ 0 };
	ll right{ MAX };
	ll middle{ 0 };

	while (left <= right)
	{
		middle = (left + right) / 2;

		ll newPercent = (Y + middle) * 100 / (X + middle);

		if (init != newPercent)
		{
			right = middle - 1;
			result = middle;
		}
		else
		{
			left = middle + 1;
		}
	}
}

void solve()
{
	bSearch();

	if (result == INF)
		cout << -1;
	else
		cout << result;
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