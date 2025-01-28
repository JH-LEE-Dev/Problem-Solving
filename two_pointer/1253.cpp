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

#define MAX 2'000'000'001
#define endl '\n'
#define INF numeric_limits<int>::max()

int N{ 0 };
vector<int> arr;
int result{ 0 };

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;

		arr.push_back(input);
	}
}

void bSearch()
{
	sort(arr.begin(), arr.begin() + N);

	for (int i{ 0 }; i < N; ++i)
	{
		int left{ 0 };
		int right{ N - 1 };
		int middle{ 0 };
		int sum{ 0 };

		while (left < right)
		{
			if (left == i)
			{
				++left;
				continue;
			}

			if (right == i)
			{
				--right;
				continue;
			}

			middle = (left + right) / 2;

			sum = arr[left] + arr[right];

			if (arr[i] == sum)
			{
				++result;
				break;
			}

			if (arr[i] > sum)
				++left;
			else
				--right;
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