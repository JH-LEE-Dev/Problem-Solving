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
#define MAX_H 500'001
#define MAX_N 200'001

int n, h;
vector<int> ceiling;
vector<int> floors;

void input()
{
	cin >> n >> h;

	for (int i{ 0 }; i < n; ++i)
	{
		int temp;
		cin >> temp;

		if (i % 2 == 0)
			floors.push_back(temp);
		else
			ceiling.push_back(temp);
	}
}

int binarySearch(int pivot)
{
	int result{ 0 };

	int left{ 0 };
	int right{ (int)floors.size() - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ floors[middle] };

		if (middleNum <= pivot)
			left = middle + 1;
		else
			right = middle - 1;
	}

	result += ((int)floors.size() - left);

	left = 0;
	right = (int)ceiling.size() - 1;

	//천장이 바닥일 때로 생각하여 구간 높이를 재설정한다.
	pivot = h - pivot - 1;

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ ceiling[middle] };

		if (middleNum <= pivot)
			left = middle + 1;
		else
			right = middle - 1;
	}

	result += ((int)ceiling.size() - left);

	return result;
}

void solve()
{
	int result{ INF };
	int cnt{ 0 };

	sort(floors.begin(), floors.end());
	sort(ceiling.begin(), ceiling.end());

	for (int i{ 0 }; i < h; ++i)
	{
		int temp{ binarySearch(i) };

		if (result > temp)
		{
			result = temp;
			cnt = 1;
		}
		else if (result == temp)
			++cnt;
	}

	cout << result << ' ' << cnt;
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