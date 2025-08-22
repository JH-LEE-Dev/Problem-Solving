#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct dat
{
	pair<int, int> factor;
	int index{ 0 };
	int order{ 0 };
};

vector<dat> arr(55);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 };

	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		dat input;
		cin >> input.factor.first >> input.factor.second;

		arr[i] = input;
	}

	for (int i = 0; i < N; ++i)
	{
		int order{ 1 };

		for (int j = 0; j < N; ++j)
		{
			if (i == j)
				continue;

			if (arr[i].factor.first < arr[j].factor.first &&
				arr[i].factor.second < arr[j].factor.second)
			{
				++order;
			}
		}

		cout << order << " ";
	}

	return 0;
}