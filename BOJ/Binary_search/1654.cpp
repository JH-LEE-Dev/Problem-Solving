#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

unsigned int result{ 0 };
unsigned int N{ 0 }, K{ 0 };
vector<unsigned int> arr(10'005, 0);

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	cin >> K >> N;

	unsigned int maxLen{ numeric_limits<int>::max() };

	for (int i = 0; i < K; i++)
	{
		cin >> arr[i];
		maxLen = min(maxLen, arr[i]);
	}

	unsigned int left{ 0 }, right{ maxLen }, mid{ 0 };

	while (left <= right)
	{
		mid = (left + right) / 2;

		unsigned int total{ 0 };

		for (int i = 0; i < K; i++)
		{
			total += arr[i] / mid;
		}

		if (total >= N)
		{
			left = mid + 1;

			result = max(result, mid);
		}
		else
		{
			right = mid - 1;
		}
	}

	cout << result;

	return 0;
}