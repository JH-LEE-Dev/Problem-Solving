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
#define MAX 301

int N, M;
vector<int> arr(MAX, 0);
int result{ INF };

int minVal{ 0 };
int maxVal{ 0 };

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> arr[i];

		minVal = max(minVal, arr[i]);
		maxVal += arr[i];
	}
}

void bSearch()
{
	int left{ minVal };
	int right{ maxVal };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int sum{ 0 };
		int cnt{ 1 };

		for (int i = 0; i < N; i++)
		{
			sum += arr[i];

			if (sum > middle)
			{
				sum = arr[i];
				++cnt;
			}
		}

		if (cnt > M)
			left = middle + 1;
		else
		{
			right = middle - 1;
		}
	}

	result = left;
}

void solve()
{
	bSearch();

	cout << result << endl;

	int sum{ 0 };
	int numCnt{ 0 };

	for (int i{ 0 }; i < N; i++)
	{
		sum += arr[i];

		if (sum > result)
		{
			sum = arr[i];
			--M;

			cout << numCnt << " ";

			numCnt = 0;
		}

		numCnt++;

		if (N - i == M)
			break;
	}

	while (M != 0)
	{
		cout << numCnt << " ";

		numCnt = 1;

		--M;
	}
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