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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

vector<int> arr(100'005, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 };
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;
		arr[i] = input;
	}

	sort(arr.begin(), arr.begin() + N);

	int left{ 0 }, right{ N - 1 };

	int minAbs{ INF };

	int leftComponent{ 0 };
	int rightComponent{ 0 };

	while (left < right)
	{
		if (arr[left] + arr[right] == 0)
		{
			leftComponent = arr[left];
			rightComponent = arr[right];
			minAbs = 0;
			break;
		}
		else
		{
			if (abs(arr[left] + arr[right]) < minAbs)
			{
				leftComponent = arr[left];
				rightComponent = arr[right];
				minAbs = abs(arr[left] + arr[right]);
			}

			if (arr[left] + arr[right] < 0)
			{
				++left;
			}
			else
			{
				--right;
			}
		}
	}

	cout << leftComponent << " " << rightComponent;

	return 0;
}