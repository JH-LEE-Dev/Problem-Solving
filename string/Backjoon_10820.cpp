#include <iostream>
#include <string>
using namespace std;

#define ASCII_UPPER_CASE_START 65
#define ASCII_UPPER_CASE_END 90

#define ASCII_LOWER_CASE_START 97
#define ASCII_LOWER_CASE_END 122

#define ASCII_NUMBER_START 48
#define ASCII_NUMBER_END 57

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	string Input;

	while (getline(cin, Input))
	{
		int lower{ 0 }, upper{ 0 }, number{ 0 }, space{ 0 };

		for (int i = 0; i < Input.length(); ++i)
		{
			int ascii_code = (int)Input[i];

			if (ascii_code >= ASCII_UPPER_CASE_START
				&& ascii_code <= ASCII_UPPER_CASE_END)
			{
				++upper;
			}

			if (ascii_code >= ASCII_LOWER_CASE_START
				&& ascii_code <= ASCII_LOWER_CASE_END)
			{
				++lower;
			}

			if (ascii_code >= ASCII_NUMBER_START
				&& ascii_code <= ASCII_NUMBER_END)
			{
				++number;
			}

			if (ascii_code == 32)
			{
				++space;
			}
		}

		cout << lower << " " << upper << " " << number << " " << space << '\n';
	}

	return 0;
}