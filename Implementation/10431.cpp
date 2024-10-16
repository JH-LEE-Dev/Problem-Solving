#include <iostream>
#include <vector>
#include <limits>

#define endl '\n'
using namespace std;

vector<int> arr(25, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int P{ 0 }, T{ 0 };

	cin >> P;

	for (int i{ 0 }; i < P; ++i)
	{
		cin >> T;

		for (int j{ 0 }; j < 20; ++j)
		{
			cin >> arr[j];
		}

		int total{ 0 };

		for (int j{ 0 }; j < 20; ++j)
		{
			for (int k{ 0 }; k < j; ++k)
			{
				if (arr[j] < arr[k])
				{
					++total;
				}
			}
		}

		cout << T << " " << total << endl;
	}

	return 0;
}