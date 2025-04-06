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
*	���� �м�
*	1. -10000 ~ 10000 �� ������ �־����� �迭.
*	2. �� �迭�� �� ������ ���� 0�� �Ǵ� ����� ���� ���Ѵ�.
*
*	���� �ذ� ����
*	1. �迭�� ������ �Ŀ�, �迭�� 2�� for loop�� ���鼭 �� ������ ���� ���� �� 0�� �� �� �ִ� ���Ҹ�
*	   ������ �κ��� �迭���� �̺� Ž���� Ȱ���ؼ� ã�´�.
*	2. -10 5 5 5 5 5 �� ���� ��쿡 ������ �ùٸ��� ����ϱ� ���ؼ�, lower_bound�� upper_bound ������ ������
*		����� ���Ѵ�.
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