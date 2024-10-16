#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define endl '\n'
using namespace std;

vector<int> arr(21, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 };
	string order;

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> order;

		if (order == "add")
		{
			int input{ 0 };
			cin >> input;

			if (!binary_search(arr.begin(), arr.end(), input))
				arr.push_back(input);
		}

		if (order == "remove")
		{
			int input{ 0 };
			cin >> input;
			arr.erase(std::remove(arr.begin(), arr.end(), input), arr.end());
		}

		if (order == "check")
		{
			int input{ 0 };
			cin >> input;

			if (binary_search(arr.begin(), arr.end(), input))
				cout << '1' << endl;
			else
				cout << '0' << endl;
		}

		if (order == "toggle")
		{
			int input{ 0 };
			cin >> input;

			if (binary_search(arr.begin(), arr.end(), input))
			{
				arr.erase(std::remove(arr.begin(), arr.end(), input), arr.end());
			}
			else
			{
				arr.push_back(input);
			}
		}

		if (order == "all")
		{
			arr = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
		}

		if (order == "empty")
		{
			arr.clear();
		}
	}

	return 0;
}