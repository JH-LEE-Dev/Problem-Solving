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
*	문제 분석
*	1. -10000 ~ 10000 의 값으로 주어지는 배열.
*	2. 이 배열의 세 원소의 합이 0이 되는 경우의 수를 구한다.
*
*	문제 해결 전략
*	1. 배열을 정렬한 후에, 배열을 2중 for loop를 돌면서 두 원소의 합을 구한 후 0이 될 수 있는 원소를
*	   나머지 부분의 배열에서 이분 탐색을 활용해서 찾는다.
*	2. -10 5 5 5 5 5 과 같은 경우에 개수를 올바르게 계산하기 위해서, lower_bound와 upper_bound 사이의 개수를
*		결과에 더한다.
*
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()

int N;
vector<int> arr;

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int num;
		cin >> num;

		arr.push_back(num);
	}
}

int lowerBound(int target, int left)
{
	int right{ N - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ (arr[middle]) };

		if (middleNum < target)
			left = middle + 1;
		else
			right = middle - 1;
	}

	return left;
}

int upperBound(int target, int left)
{
	int right{ N - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ (arr[middle]) };

		if (middleNum <= target)
			left = middle + 1;
		else
			right = middle - 1;
	}

	return left;
}

void solve()
{
	sort(arr.begin(), arr.end());

	long long result{ 0 };

	for (int i{ 0 }; i < N - 2; ++i)
	{
		for (int j{ i + 1 }; j < N - 1; ++j)
		{
			auto partial_sum{ arr[i] + arr[j] };

			auto left{ lowerBound(0 - partial_sum,j + 1) };
			auto right{ upperBound(0 - partial_sum,j + 1) };

			result += (right - left);
		}
	}

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