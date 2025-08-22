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

vector<int> arr;
vector<int> partial;
int N;
int maxVal{ -1 };

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

void bSearch(int target, int total)
{
	int left{ 0 };
	int right{ (int)partial.size() - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ partial[middle] };

		if (target > middleNum)
			left = middle + 1;
		else
			right = middle - 1;
	}

	if (left < (int)partial.size() - 1 && partial[left] == target)
	{
		maxVal = total;
		return;
	}
}

void solve()
{
	sort(arr.begin(), arr.end());

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			partial.push_back(arr[i] + arr[j]);
		}
	}

	sort(partial.begin(), partial.end());

	for (int i{ N - 1 }; i >= 0; --i)
	{
		for (int j{ i }; j >= 0; --j)
		{
			bSearch(arr[i] - arr[j], arr[i]);

			if (maxVal != -1)
			{
				cout << maxVal;
				return;
			}
		}
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