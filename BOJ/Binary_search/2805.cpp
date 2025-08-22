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
#define INF numeric_limits<int>::max()
#define MAX 1'000'001

int N{ 0 }, M{ 0 };
vector<ll> woods(MAX, 0);
ll maxH{ -1 };
ll result{ -1 };

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> woods[i];
		maxH = max(maxH, woods[i]);
	}
}

void binSearch()
{
	ll left{ 0 };
	ll right{ maxH };
	ll middle{ 0 };

	while (left <= right)
	{
		middle = (left + right) / 2;

		ll totalH{ 0 };

		for (int i{ 0 }; i < N; ++i)
		{
			if (woods[i] > middle)
			{
				totalH += woods[i] - middle;
			}
		}

		if (totalH >= M)
		{
			left = middle + 1;
			result = max(result, middle);
		}
		else
		{
			right = middle - 1;
		}
	}
}

void solve()
{
	binSearch();

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