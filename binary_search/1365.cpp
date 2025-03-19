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

int N;
vector<int> arr;

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int temp;
		cin >> temp;

		arr.push_back(temp);
	}
}

int bSearch(int target, vector<int>& LIS)
{
	int left{ 0 };
	int right{ (int)LIS.size() - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ LIS[middle] };

		if (middleNum < target)
			left = middle + 1;
		else
			right = middle - 1;
	}

	return left;
}

void solve()
{
	vector<int> LIS;

	for (int i{ 0 }; i < N; ++i)
	{
		int idx{ bSearch(arr[i],LIS) };

		if (idx == LIS.size())
		{
			LIS.push_back(arr[i]);
		}
		else
		{
			LIS[idx] = arr[i];
		}
	}

	cout << arr.size() - LIS.size();
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