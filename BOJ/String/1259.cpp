#include <iostream>
#include <string>
using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	string input;

	while (1)
	{
		cin >> input;
		if (input == "0")
			return 0;

		int length = input.length();

		bool isPalinDrome{ true };

		for (int i = 0; i < length / 2; ++i)
		{
			if (input[0] == '0')
			{
				isPalinDrome = false;
				break;
			}

			if (input[i] != input[length - i - 1])
			{
				isPalinDrome = false;
				break;
			}
		}

		if (isPalinDrome)
			cout << "yes" << '\n';
		else
			cout << "no" << '\n';
	}

	return 0;
}
