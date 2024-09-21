#include <iostream>
#include <vector>
using namespace std;

vector<int> arr(105, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 }, M{ 0 }, result{ 0 };

	cin >> N >> M;

	for (int i = 0; i < N; ++i)
	{
		cin >> arr[i];
	}

	for (int i = 0; i < N - 2; ++i)
	{
		int sum{ 0 };

		sum += arr[i];

		if (sum >= M)
			continue;

		for (int j = i + 1; j < N - 1; ++j)
		{
			sum += arr[j];

			if (sum >= M)
			{
				sum -= arr[j];
				continue;
			}

			for (int k = j + 1; k < N; ++k)
			{
				sum += arr[k];

				if (sum <= M)
				{
					result = max(result, sum);
				}

				sum -= arr[k];
			}

			sum -= arr[j];
		}
	}

	cout << result;

	return 0;
}