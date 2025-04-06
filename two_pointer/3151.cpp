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
*	-�̺� Ž��-
*	1. �迭�� ������ �Ŀ�, �迭�� 2�� for loop�� ���鼭 �� ������ ���� ���� �� 0�� �� �� �ִ� ���Ҹ�
*	   ������ �κ��� �迭���� �̺� Ž���� Ȱ���ؼ� ã�´�.
*	2. -10 5 5 5 5 5 �� ���� ��쿡 ������ �ùٸ��� ����ϱ� ���ؼ�, lower_bound�� upper_bound ������ ������
*		����� ���Ѵ�.
*
*	-�� ������-
*	1. �迭�� for loop�� ��ȸ�ϸ�, i��° �ε��� ������ �κ� �迭���� �� �����ͷ� 0-arr[i]�� �����ϴ� ��츦 ã�´�.
*	2. �ߺ��� �ùٸ��� ����ϱ� ���ؼ�, arr[left] == arr[right]�� ���� nCr�� ������ ����ϰ�, arr[left] != arr[right]�� ����
*	   while���� ����Ͽ� ��� �ߺ� ��츦 ����Ѵ�.
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