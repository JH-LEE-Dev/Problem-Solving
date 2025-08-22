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

int N{ 0 }, K{ 0 };
vector<int> arr;
ll total{ 0 }, result{ 0 };

void input()
{
	cin >> N >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;

		arr.push_back(input);
		total += input;
	}
}

int sum(int middle)
{
	ll tempSum{ 0 };
	int cnt{ 1 };

	for (int i{ 0 }; i < N; ++i)
	{
		if (arr[i] > middle)
		{
			cnt = INF;
			break;
		}

		if (tempSum + arr[i] > middle)
		{
			++cnt;
			tempSum = arr[i];
		}
		else
		{
			tempSum += arr[i];
		}
	}

	return cnt;
}

void bSearch()
{
	ll left{ 1 };
	ll right{ total };
	ll middle{ 0 };

	while (left <= right)
	{
		middle = (left + right) / 2;

		auto tempCnt{ sum(middle) };

		if (tempCnt > K)
		{
			left = middle + 1;
		}
		else
		{
			result = middle;
			right = middle - 1;
		}
	}
}

void solve()
{
	bSearch();

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