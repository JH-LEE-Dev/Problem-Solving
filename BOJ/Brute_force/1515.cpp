#include <iostream>
#include <vector>
#include <string>

#define endl '\n'
using namespace std;

#define MAX 30000

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	string input;

	cin >> input;

	int num{ 0 }, idx{ 0 };

	while (num++ < MAX)
	{
		string toString = to_string(num);

		for (int i = 0; i < toString.length(); ++i)
		{
			if (input[idx] == toString[i])
			{
				++idx;
			}

			if (idx == input.length())
			{
				cout << num;

				return 0;
			}
		}
	}

	return 0;
}