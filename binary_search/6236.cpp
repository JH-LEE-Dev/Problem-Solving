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
#define INF numeric_limits<int>::max()
using ll = long long;

int N, M;
vector<int> money;
ll totalMoney;

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		int temp;
		cin >> temp;

		money.push_back(temp);

		totalMoney += temp;
	}
}

int binarySearch()
{
	ll left{ 0 };
	ll right{ totalMoney };

	while (left <= right)
	{
		ll middle{ (left + right) / 2 };

		ll usedMoney{ middle };
		ll cnt{ 1 };

		bool isValid{ true };

		for (int i{ 0 }; i < N; ++i)
		{
			if (usedMoney - money[i] < 0)
			{
				++cnt;
				usedMoney = middle - money[i];

				if (usedMoney < 0)
				{
					isValid = false;
					break;
				}
			}
			else
			{
				usedMoney -= money[i];
			}
		}

		if (isValid == false)
		{
			left = middle + 1;
			continue;
		}

		if (cnt <= M)
		{
			right = middle - 1;
		}
		else
		{
			left = middle + 1;
		}
	}

	return left;
}

void solve()
{
	cout << binarySearch();
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