#include <iostream>
#include <vector>
#define endl '\n'
using namespace std;

vector<bool> mySwitch(105, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 }, T{ 0 };

	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		int input{ 0 };
		cin >> input;
		mySwitch[i] = (bool)input;
	}

	cin >> T;

	for (int i{ 0 }; i < T; ++i)
	{
		int sex{ 0 }, input{ 0 };

		cin >> sex >> input;

		if (sex == 1)
		{
			for (int j{ input }; j <= N; j += input)
			{
				mySwitch[j] = !mySwitch[j];
			}
		}
		else
		{
			mySwitch[input] = !mySwitch[input];

			for (int j{ 1 }; j <= input; ++j)
			{
				if (input + j <= N && input - j >= 1)
				{
					if (mySwitch[input + j] == mySwitch[input - j])
					{
						mySwitch[input + j] = !mySwitch[input + j];
						mySwitch[input - j] = !mySwitch[input - j];
					}
					else
					{
						break;
					}
				}
			}
		}
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		cout << mySwitch[i] << " ";

		if (i % 20 == 0)
			cout << endl;
	}


	return 0;
}