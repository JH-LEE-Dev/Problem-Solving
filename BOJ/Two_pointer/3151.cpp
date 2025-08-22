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
*	-이분 탐색-
*	1. 배열을 정렬한 후에, 배열을 2중 for loop를 돌면서 두 원소의 합을 구한 후 0이 될 수 있는 원소를
*	   나머지 부분의 배열에서 이분 탐색을 활용해서 찾는다.
*	2. -10 5 5 5 5 5 과 같은 경우에 개수를 올바르게 계산하기 위해서, lower_bound와 upper_bound 사이의 개수를
*		결과에 더한다.
*
*	-투 포인터-
*	1. 배열을 for loop로 순회하며, i번째 인덱스 이후의 부분 배열에서 투 포인터로 0-arr[i]를 만족하는 경우를 찾는다.
*	2. 중복을 올바르게 계산하기 위해서, arr[left] == arr[right]인 경우는 nCr로 조합을 계산하고, arr[left] != arr[right]인 경우는
*	   while문을 사용하여 모든 중복 경우를 계산한다.
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

int twoPointer(int target, int left)
{
	int right{ N - 1 };
	int cnt{ 0 };

	while (left < right)
	{
		auto partial_sum{ arr[left] + arr[right] };

		if (partial_sum < target)
		{
			++left;
		}
		else if (partial_sum > target)
		{
			--right;
		}
		else
		{
			if (arr[left] == arr[right])
			{
				auto n{ right - left + 1 };
				auto r{ 2 };

				auto nCr{ (n * (n - 1) / 2) };

				cnt += nCr;

				return cnt;
			}
			else
			{
				auto l_cnt{ 0 };
				auto r_cnt{ 0 };

				while (true)
				{
					if (arr[left + l_cnt] == arr[left])
						++l_cnt;
					else
						break;
				}

				while (true)
				{
					if (arr[right - r_cnt] == arr[right])
						++r_cnt;
					else
						break;
				}

				cnt += l_cnt * r_cnt;

				left += l_cnt;
				right -= r_cnt;
			}
		}
	}

	return cnt;
}

void solve()
{
	sort(arr.begin(), arr.end());

	long long result{ 0 };

	for (int i{ 0 }; i < N - 2; ++i)
	{
		result += twoPointer(0 - arr[i], i + 1);
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