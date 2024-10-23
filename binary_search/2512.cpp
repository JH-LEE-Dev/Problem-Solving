#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

#define MAX 10'005
vector<int> deposit(MAX, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 }, limit{ 0 };

	cin >> N;

	int maxDeposit{ 0 };
	for (int i{ 0 }; i < N; ++i)
	{
		cin >> deposit[i];
		maxDeposit = max(deposit[i], maxDeposit);
	}
	cin >> limit;

	int left{ 1 };
	int right{ maxDeposit };
	int mid{ 0 };
	int result{ 0 };

	while (left <= right)
	{
		mid = (left + right) / 2;

		int total{ 0 };

		for (int i{ 0 }; i < N; ++i)
		{
			if (deposit[i] >= mid)
			{
				total += mid;
			}
			else
			{
				total += deposit[i];
			}
		}

		if (total <= limit)
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